// ServerLauncher.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

#ifdef CAF_WINDOWS
#	include <WinSock2.h>
#else
#	include <arpa/inet.h>
#endif

CAF_PUSH_WARNINGS
#include "WeizenbierProto.h"
CAF_POP_WARNINGS

#include "patterns/Singleton.h"


CAF_BEGIN_TYPE_ID_BLOCK(server_launcher, first_custom_type_id)

	CAF_ADD_ATOM(server_launcher, kickoff_atom)

	CAF_ADD_ATOM(server_launcher, chat_request_atom)
	CAF_ADD_ATOM(server_launcher, chat_response_atom)
	CAF_ADD_ATOM(server_launcher, chat_notification_atom)
	CAF_ADD_ATOM(server_launcher, chat_broadcast_atom)

	CAF_ADD_ATOM(server_launcher, login_request_atom)

CAF_END_TYPE_ID_BLOCK(server_launcher)


class GlobalContext
{
public:
	int RegisterActor(caf::io::connection_handle hdl, const caf::actor& actor)
	{
		m_actorMap.emplace(std::make_pair(hdl, actor));
		return 0;
	}

	std::map<caf::io::connection_handle, caf::actor>& GetActorMap()
	{
		return m_actorMap;
	}

	void SetServerActor(const caf::actor& actor)
	{
		serverActor = std::move(actor);
	}

	const caf::actor& GetServerActor()
	{
		return serverActor;
	}

private:
	std::map<caf::io::connection_handle, caf::actor> m_actorMap;
	caf::actor serverActor;
};

auto GlobalContextInstance = Singleton<GlobalContext>::Get();


// Utility function to print an exit message with custom name
void print_on_exit(caf::scheduled_actor* self, const std::string& name)
{
	self->attach_functor(
		[=](const caf::error& reason)
	{
		caf::aout(self) << name << " exited : " << caf::to_string(reason) << std::endl;
	}
	);
}


caf::behavior chatResponse(caf::event_based_actor* self)
{
	print_on_exit(self, "chat response");

	return {
		[=](chat_request_atom, std::string value)
	{
		return caf::make_message(chat_response_atom_v, value);
	},
		[=](login_request_atom, std::string stream)
	{
		return caf::make_message(login_request_atom_v, stream);
},
	};
}


template <typename AT>
AT ToActorMessageArg(const std::string& stream)
{
	google::protobuf::Any am;
	am.ParseFromArray(stream.data(), static_cast<int>(stream.size()));

	AT message;
	am.UnpackTo(&message);

	return message;
}


template <typename MT>
void WriteProtobufMessage(caf::io::broker* self, caf::io::connection_handle hdl, wzbgame::message::MessageType type, MT data)
{
	wzbgame::message::WrappedMessage wm;
	wm.set_type(type);
	wm.mutable_message()->PackFrom(data);

	auto buf = wm.SerializeAsString();
	auto bufSize = htonl(static_cast<uint32_t>(buf.size()));
	self->write(hdl, sizeof(uint32_t), &bufSize);
	self->write(hdl, buf.size(), buf.data());
	self->flush(hdl);
}


void TransferNetworkMessage(caf::io::broker* self, caf::io::connection_handle hdl, const caf::actor& buddy)
{
	print_on_exit(self, "protobuf_io");
	caf::aout(self) << "protobuf broker started" << std::endl;

	self->monitor(buddy);
	self->set_down_handler(
		[=](const caf::down_msg& dm)
	{
		if (dm.source == buddy)
		{
			caf::aout(self) << "our buddy is down" << std::endl;
			self->quit(dm.reason);
		}
	}
	);

	auto write = [=](const wzbgame::message::chat::ChatProtocol& p)
	{
		std::string buf = p.SerializeAsString();
		auto s = htonl(static_cast<uint32_t>(buf.size()));
		self->write(hdl, sizeof(uint32_t), &s);
		self->write(hdl, buf.size(), buf.data());
		self->flush(hdl);
	};

	auto writeNotification = [=](const wzbgame::message::chat::ChatNotification& p)
	{
		std::string buf = p.SerializeAsString();
		auto s = htonl(static_cast<uint32_t>(buf.size()));
		self->write(hdl, sizeof(uint32_t), &s);
		self->write(hdl, buf.size(), buf.data());
		self->flush(hdl);
	};

	auto defaultCallbacks = caf::message_handler{
		[=](const caf::io::connection_closed_msg&)
	{
		caf::aout(self) << "connection closed" << std::endl;
		self->send_exit(buddy, caf::exit_reason::remote_link_unreachable);
		self->quit(caf::exit_reason::remote_link_unreachable);
},
[=](chat_request_atom, std::string str)
{
	caf::aout(self) << "'request' " << str << std::endl;
	wzbgame::message::chat::ChatRequest p;
	p.set_message(str);
	WriteProtobufMessage(self, hdl, wzbgame::message::MessageType::ChatRequest, p);
},
[=](chat_response_atom, std::string str)
{
	caf::aout(self) << "'response' " << str << std::endl;
	wzbgame::message::chat::ChatResponse p;
	p.set_message(str);
	WriteProtobufMessage(self, hdl, wzbgame::message::MessageType::ChatResponse, p);

	self->send(GlobalContextInstance->GetServerActor(), chat_broadcast_atom_v, "", str);
},
[=](chat_notification_atom, std::string name, std::string message)
{
	//caf::aout(self) << "'notification' -> name : " << name << ", message : " << message << std::endl;
	wzbgame::message::chat::ChatNotification p;
	p.set_name(name);
	p.set_message(message);
	WriteProtobufMessage(self, hdl, wzbgame::message::MessageType::ChatNotification, p);
},
[=](login_request_atom, std::string requestMessageStream)
{
	auto message = ToActorMessageArg<wzbgame::message::login::LoginRequest>(requestMessageStream);
	
	caf::aout(self) << "login account id : " << message.account_id() << std::endl;
	
	wzbgame::message::login::LoginResponse response;
	response.set_result(wzbgame::type::result::Succeed);
	WriteProtobufMessage(self, hdl, wzbgame::message::MessageType::LoginResponse, response);
},
	};

	auto awaitProtobufData = caf::message_handler{
		[=](const caf::io::new_data_msg& msg)
	{
		wzbgame::message::WrappedMessage p;
		p.ParseFromArray(msg.buf.data(), static_cast<int>(msg.buf.size()));

		switch (p.type())
		{
		case wzbgame::message::LoginRequest:
		{
			self->send(buddy, login_request_atom_v, p.message().SerializeAsString());
		}
		break;

		case wzbgame::message::ChatRequest:
		{
			wzbgame::message::chat::ChatRequest pm;
			p.message().UnpackTo(&pm);
			self->send(buddy, chat_request_atom_v, pm.message());
		}
		break;

		//case wzbgame::message::UnknownMessageType:
		default:
		{
			self->quit(caf::exit_reason::user_shutdown);
			std::cerr << "neither Request nor Response!" << std::endl;
		}
		}

		// Receive next length prefix
		self->configure_read(hdl, caf::io::receive_policy::exactly(sizeof(uint32_t)));
		self->unbecome();
},
	}.or_else(defaultCallbacks);

	auto awaitLengthPrefix = caf::message_handler{
		[=](const caf::io::new_data_msg& msg)
	{
		uint32_t num_bytes;
		memcpy(&num_bytes, msg.buf.data(), sizeof(uint32_t));
		num_bytes = htonl(num_bytes);
	
		if (num_bytes > (1024 * 1024))
		{
			caf::aout(self) << "someone is trying something nasty" << std::endl;
			self->quit(caf::exit_reason::user_shutdown);
			return;
		}

		// Receive protobuf data
		auto nb = static_cast<size_t>(num_bytes);
		self->configure_read(hdl, caf::io::receive_policy::exactly(nb));
		self->become(caf::keep_behavior, awaitProtobufData);
},
	}.or_else(defaultCallbacks);

	// initial setup
	self->configure_read(hdl, caf::io::receive_policy::exactly(sizeof(uint32_t)));
	self->become(awaitLengthPrefix);
}


caf::behavior server(caf::io::broker* self)
{
	print_on_exit(self, "server");
	caf::aout(self) << "server is running" << std::endl;

	auto newConnectionHandler = [=](const caf::io::new_connection_msg& msg)
	{
		caf::aout(self) << "server accepted new connection" << std::endl;

		auto chatResponseActor = self->system().spawn(chatResponse);

		auto clientActor = self->fork(TransferNetworkMessage, msg.handle, chatResponseActor);

		// std::move() 가 진행되므로 clientActor 에 대한 모든 접근은 이전에 처리해야 한다.
		GlobalContextInstance->RegisterActor(msg.handle, clientActor);

		// only accept 1 connection in our example
		//self->quit();
	};

	auto chatBroadcastHandler = [=](chat_broadcast_atom, std::string name, std::string message)
	{
		auto actorMap = GlobalContextInstance->GetActorMap();

		for (const auto& clientActorInfo : GlobalContextInstance->GetActorMap())
		{
			self->send(clientActorInfo.second, chat_notification_atom_v, name, message);
		}
	};

	return { newConnectionHandler, chatBroadcastHandler, };
}


class config : public caf::actor_system_config
{
public:
	uint16_t port = 0;
	std::string host = "localhost";

	config()
	{
		opt_group{ custom_options_, "global" }
		.add(port, "port,p", "set port");
	}
};


void RunServer(caf::actor_system& system, const config& cfg)
{
	std::cout << "run server" << std::endl;

	auto serverActor = system.middleman().spawn_server(server, cfg.port);

	if (!serverActor)
	{
		std::cerr << "unable to spawn server : " << caf::to_string(serverActor.error()) << std::endl;
	}

	GlobalContextInstance->SetServerActor(serverActor.value());

	std::cout << "*** press [enter] to quit" << std::endl;

	std::string dummy;
	std::getline(std::cin, dummy);
	std::cout << "... cya" << std::endl;
}


void caf_main(caf::actor_system& system, const config& cfg)
{
	RunServer(system, cfg);
}

CAF_MAIN(caf::id_block::server_launcher, caf::io::middleman)

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
