﻿// TestClient.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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
#include "chat.pb.h"
#include "adapter.pb.h"
CAF_POP_WARNINGS


CAF_BEGIN_TYPE_ID_BLOCK(test_client, first_custom_type_id)

    CAF_ADD_ATOM(test_client, kickoff_atom)

    CAF_ADD_ATOM(test_client, chat_request_atom)
    CAF_ADD_ATOM(test_client, chat_response_atom)
    CAF_ADD_ATOM(test_client, chat_notification_atom)

CAF_END_TYPE_ID_BLOCK(test_client)


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


struct chat_state
{
    size_t count = 0;
};

struct ChatMessage
{
    std::string str;
};

std::istream& operator>>(std::istream& is, ChatMessage& msg)
{
    std::getline(is, msg.str);
    return is;
}

struct ClientInfo
{
    std::string name;
    size_t pingCount = 0;
};


caf::behavior chatRequest(caf::stateful_actor<ClientInfo>* self, std::string accountName)
{
	print_on_exit(self, "chat request");

    const size_t num_pings = 20u;

    self->state.name = accountName;

	return {
		[=](kickoff_atom, const caf::actor& chatResponse)
	{
		//self->send(chatResponse, chat_request_atom_v, std::to_string(1));

		self->become({
			[=](caf::pong_atom, int value) -> caf::result<caf::ping_atom, int>
		{
			if (++(self->state.pingCount) >= num_pings)
			{
				//self->quit();
			}

			return { caf::ping_atom_v, value + 1 };
},
			[=](chat_response_atom, std::string str) -> caf::result<chat_request_atom, std::string>
		{
			return {};
		},
	[=](chat_request_atom, std::string str) -> caf::result<chat_request_atom, std::string>
		{
			return { chat_request_atom_v, str };
},
[=](chat_notification_atom, std::string str) -> caf::result<chat_notification_atom, std::string>
{
	return { chat_notification_atom_v, str };
},
}
		);
},
	};
}


void protobuf_io(caf::io::broker* self, caf::io::connection_handle hdl, const caf::actor& buddy)
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
    wzbgame::message::chat::ChatProtocol p;
    p.mutable_request()->set_message(str);
    write(p);
},
[=](chat_response_atom, std::string str)
{
    caf::aout(self) << "'response' " << str << std::endl;
    wzbgame::message::chat::ChatProtocol p;
    p.mutable_response()->set_message(str);
    write(p);
},
[=](chat_notification_atom, std::string str)
{
    caf::aout(self) << "'notification' " << str << std::endl;
},
    };

    auto awaitProtobufData = caf::message_handler{
        [=](const caf::io::new_data_msg& msg)
    {
        wzbgame::message::WrappedMessage p;
        p.ParseFromArray(msg.buf.data(), static_cast<int>(msg.buf.size()));

		switch (p.type())
		{
		case wzbgame::message::ChatRequest:
		{
            wzbgame::message::chat::ChatRequest pm;
            p.message().UnpackTo(&pm);
			self->send(buddy, chat_request_atom_v, pm.message());
		}
		break;

		case wzbgame::message::ChatResponse:
		{
            wzbgame::message::chat::ChatResponse pm;
            p.message().UnpackTo(&pm);
            self->send(buddy, chat_response_atom_v, pm.message());
		}
		break;

        case wzbgame::message::ChatNotification:
        {
            wzbgame::message::chat::ChatNotification pm;
            p.message().UnpackTo(&pm);
            self->send(buddy, chat_notification_atom_v, pm.message());
        }
        break;

        //case wzbgame::message::UnknownMessageType:
        default:
		{
			self->quit(caf::exit_reason::user_shutdown);
			std::cerr << "Invalid Message~!" << std::endl;
		}
		}

        // Receive next length prefix
        self->configure_read(hdl, caf::io::receive_policy::exactly(sizeof(uint32_t)));
        self->unbecome();
},
    }.or_else(defaultCallbacks);

    auto awaitLengthPrefix = caf::message_handler
    {
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


class config : public caf::actor_system_config
{
public:
    uint16_t port = 0;
    std::string host = "localhost";

    config()
    {
        opt_group{ custom_options_, "global" }
            .add(port, "port,p", "set port")
            .add(host, "host,H", "set host");
    }
};


void RunClient(caf::actor_system& system, const config& cfg)
{
    std::cout << "run test client" << std::endl;

    std::string accountName;

    if (auto nameByConfig = caf::get_if<std::string>(&cfg, "name"))
    {
        accountName = *nameByConfig;
    }

    while (accountName.empty())
    {
        std::cout << "please enter your account name : " << std::flush;

        if (!std::getline(std::cin, accountName))
        {
            std::cerr << "*** no name given... terminating" << std::endl;
            return;
        }
    }

    auto chatRequestActor = system.spawn(chatRequest, accountName);
    auto io_actor = system.middleman().spawn_client(protobuf_io, cfg.host, cfg.port, chatRequestActor);

    if (!io_actor)
    {
        std::cout << "cannot connect to " << cfg.host << " at port" << cfg.port << " : " << caf::to_string(io_actor.error()) << std::endl;
        return;
    }

    caf::send_as(*io_actor, chatRequestActor, kickoff_atom_v, *io_actor);


	std::cout << "*** starting client, type '/help' for a list of commands\n";
	std::istream_iterator<ChatMessage> eof;
	std::vector<std::string> words;

	for (std::istream_iterator<ChatMessage> input{ std::cin }; input != eof; ++input)
	{
		if (input->str.empty())
		{
			// Ignore empty lines.
		}
		else if (input->str[0] == '/')
		{
			words.clear();
			split(words, input->str, caf::is_any_of(" "));

			if (words.size() == 1 && words[0] == "/quit")
			{
				std::cin.setstate(std::ios_base::eofbit);
			}
			else
			{
				std::cout << "*** available commands : \n"
					"\t/quit              quit the program\n"
					"\t/help              print this text\n";
			}
		}
		else
		{
			caf::send_as(*io_actor, chatRequestActor, chat_request_atom_v, input->str);
		}
	}
}


void caf_main(caf::actor_system& system, const config& cfg)
{
    RunClient(system, cfg);
}

CAF_MAIN(caf::id_block::test_client, caf::io::middleman)


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.