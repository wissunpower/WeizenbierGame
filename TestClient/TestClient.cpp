// TestClient.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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


CAF_BEGIN_TYPE_ID_BLOCK(test_client, first_custom_type_id)

    CAF_ADD_ATOM(test_client, send_to_server_atom)

    CAF_ADD_ATOM(test_client, chat_request_atom)
    CAF_ADD_ATOM(test_client, chat_response_atom)
    CAF_ADD_ATOM(test_client, chat_notification_atom)

    CAF_ADD_ATOM(test_client, login_request_atom)
    CAF_ADD_ATOM(test_client, login_response_atom)

    CAF_ADD_ATOM(test_client, character_create_request_atom)
    CAF_ADD_ATOM(test_client, character_create_response_atom)
    CAF_ADD_ATOM(test_client, character_delete_request_atom)
    CAF_ADD_ATOM(test_client, character_delete_response_atom)
    CAF_ADD_ATOM(test_client, character_select_request_atom)
    CAF_ADD_ATOM(test_client, character_select_response_atom)

    CAF_ADD_ATOM(test_client, ingame_enter_request_atom)
    CAF_ADD_ATOM(test_client, ingame_enter_response_atom)


    CAF_ADD_TYPE_ID(test_client, (wzbgame::model::Position))

CAF_END_TYPE_ID_BLOCK(test_client)


namespace caf
{
    template <>
    struct inspector_access<wzbgame::model::Position> : inspector_access_base<wzbgame::model::Position>
    {
        template <typename Inspector>
        static bool apply(Inspector& f, wzbgame::model::Position& src)
        {
            //return f.object(src).fields(f.field("pointX", src.point_x()),
            //							f.field("pointY", src.point_y()),
            //							f.field("pointZ", src.point_z()));

            return true;
        }
    };
}


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


template <typename MT>
wzbgame::message::WrappedMessage MakeWrappedMessage(wzbgame::message::MessageType type, MT data)
{
    wzbgame::message::WrappedMessage wrapped;
    wrapped.set_type(type);
    wrapped.mutable_message()->PackFrom(data);

    return wrapped;
}


caf::behavior HandleMessage(caf::stateful_actor<ClientInfo>* self)
{
	print_on_exit(self, "message handler");

    return {
        [=](chat_request_atom, std::string str)
    {
        caf::aout(self) << "'request' " << str << std::endl;
        wzbgame::message::chat::ChatRequest p;
        p.set_message(str);
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::ChatRequest, p);

        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](chat_response_atom, std::string str)
    {
        return caf::make_message();
    },
        [=](chat_notification_atom, std::string accountID, std::string chatMessage)
    {
        caf::aout(self) << accountID << " : " << chatMessage << std::endl;
        
        return caf::make_message();
    },
        [=](login_response_atom, int result)
    {
        return caf::make_message();
    },
        [=](login_request_atom, std::string accountID)
    {
        caf::aout(self) << "Try Login -> Account ID : " << accountID << std::endl;
        
        wzbgame::message::login::LoginRequest p;
        p.set_account_id(accountID);
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::LoginRequest, p);

        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](login_response_atom, int result)
    {
        caf::aout(self) << "Login Result : " << result << std::endl;

        return caf::make_message();
    },
        [=](character_create_request_atom, std::string characterID)
    {
        caf::aout(self) << "Try Character Create -> Character ID : " << characterID << std::endl;
        wzbgame::message::lobby::CharacterCreateRequest p;
        p.set_character_id(characterID);
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterCreateRequest, p);
        
        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](character_create_response_atom, int result)
    {
        caf::aout(self) << "Character Create Result : " << result << std::endl;
        
        return caf::make_message();
    },
        [=](character_delete_request_atom, std::string characterID)
    {
        caf::aout(self) << "Try Character Delete -> Character ID : " << characterID << std::endl;
        
        wzbgame::message::lobby::CharacterDeleteRequest p;
        p.set_character_id(characterID);
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterDeleteRequest, p);
        
        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](character_delete_response_atom, int result)
    {
        caf::aout(self) << "Character Delete Result : " << result << std::endl;
        
        return caf::make_message();
    },
        [=](character_select_request_atom, std::string characterID)
    {
        caf::aout(self) << "Try Character Select -> Character ID : " << characterID << std::endl;
        
        wzbgame::message::lobby::CharacterSelectRequest p;
        p.set_character_id(characterID);
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterSelectRequest, p);
        
        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](character_select_response_atom, int result)
    {
        caf::aout(self) << "Character Select Result : " << result << std::endl;
        
        return caf::make_message();
    },
        [=](ingame_enter_request_atom, std::string characterID)
    {
        caf::aout(self) << "Try InGame Enter -> Character ID : " << characterID << std::endl;

        wzbgame::message::lobby::InGameEnterRequest p;
        p.set_character_id(characterID);
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::InGameEnterRequest, p);

        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](ingame_enter_response_atom, int result, wzbgame::model::Position startingPosition)
    {
        caf::aout(self) << "InGame Enter Result : " << result << std::endl;
        caf::aout(self) << "Starting Position -> X : " << startingPosition.point_x() << ", Y : " << startingPosition.point_y() << ", Z : " << startingPosition.point_z() << std::endl;

        return caf::make_message();
    },
    };
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
    print_on_exit(self, "network message transfer");
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

    auto sendToServer = [=](const std::string& messageStream)
    {
        auto bufSize = htonl(static_cast<uint32_t>(messageStream.size()));
        self->write(hdl, sizeof(uint32_t), &bufSize);
        self->write(hdl, messageStream.size(), messageStream.data());
        self->flush(hdl);
    };

    auto defaultCallbacks = caf::message_handler{
        [=](const caf::io::connection_closed_msg&)
    {
        caf::aout(self) << "connection closed" << std::endl;
        self->send_exit(buddy, caf::exit_reason::remote_link_unreachable);
        self->quit(caf::exit_reason::remote_link_unreachable);
    },
        [=](send_to_server_atom, std::string messageStream)
    {
        sendToServer(messageStream);
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
            self->send(buddy, chat_notification_atom_v, pm.name(), pm.message());
        }
        break;

        case wzbgame::message::LoginResponse:
        {
            wzbgame::message::login::LoginResponse pm;
            p.message().UnpackTo(&pm);
            self->send(buddy, login_response_atom_v, pm.result());
        }
        break;

        case wzbgame::message::CharacterCreateResponse:
        {
            wzbgame::message::lobby::CharacterCreateResponse pm;
            p.message().UnpackTo(&pm);
            self->send(buddy, character_create_response_atom_v, pm.result());
        }
        break;

        case wzbgame::message::CharacterDeleteResponse:
        {
            wzbgame::message::lobby::CharacterDeleteResponse pm;
            p.message().UnpackTo(&pm);
            self->send(buddy, character_delete_response_atom_v, pm.result());
        }
        break;

        case wzbgame::message::CharacterSelectResponse:
        {
            wzbgame::message::lobby::CharacterSelectResponse pm;
            p.message().UnpackTo(&pm);
            self->send(buddy, character_select_response_atom_v, pm.result());
        }
        break;

        case wzbgame::message::InGameEnterResponse:
        {
            wzbgame::message::lobby::InGameEnterResponse pm;
            p.message().UnpackTo(&pm);
            self->send(buddy, ingame_enter_response_atom_v, pm.result(), pm.position());
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

    auto messageHandleActor = system.spawn(HandleMessage);
    auto messageTransferActor = system.middleman().spawn_client(TransferNetworkMessage, cfg.host, cfg.port, messageHandleActor);

    if (!messageTransferActor)
    {
        std::cout << "cannot connect to " << cfg.host << " at port" << cfg.port << " : " << caf::to_string(messageTransferActor.error()) << std::endl;
        return;
    }


    // 임시 코드, messageTransferActor 코드를 먼저 실행하며 std 출력을 조정하기 위함.
    std::this_thread::sleep_for(std::chrono::milliseconds{ 1 });


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

    caf::send_as(*messageTransferActor, messageHandleActor, login_request_atom_v, accountName);


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
            else if (words.size() >= 2 && words[0] == "/charcreate")
            {
                caf::send_as(*messageTransferActor, messageHandleActor, character_create_request_atom_v, words[1]);
            }
            else if (words.size() >= 2 && words[0] == "/chardelete")
            {
                caf::send_as(*messageTransferActor, messageHandleActor, character_delete_request_atom_v, words[1]);
            }
            else if (words.size() >= 2 && words[0] == "/charselect")
            {
                caf::send_as(*messageTransferActor, messageHandleActor, character_select_request_atom_v, words[1]);
            }
            else if (words.size() >= 2 && words[0] == "/ingameenter")
            {
                caf::send_as(*messageTransferActor, messageHandleActor, ingame_enter_request_atom_v, words[1]);
            }
            else
			{
				std::cout << "*** available commands : \n"
					"\t/quit              quit the program\n"
                    "\t/charcreate        create character\n"
                    "\t/chardelete        delete character\n"
                    "\t/charselect        select character\n"
                    "\t/ingameenter       enter ingame\n"
                    "\t/help              print this text\n";
			}
		}
		else
		{
			caf::send_as(*messageTransferActor, messageHandleActor, chat_request_atom_v, input->str);
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
