
#include    "caf/all.hpp"

#ifdef CAF_WINDOWS
#	include <WinSock2.h>
#else
#	include <arpa/inet.h>
#endif

CAF_PUSH_WARNINGS
#include    "WeizenbierProto.h"
CAF_POP_WARNINGS

#include    "AtomDef.h"
#include	"BotBrokerImpl.h"


void BotBrokerHandler(caf::io::broker* self, caf::io::connection_handle hdl, const caf::actor& buddy)
{
    self->attach_functor(
        [=](const caf::error& reason)
    {
        caf::aout(self) << "bot broker handler" << " exited : " << caf::to_string(reason) << std::endl;
    }
    );

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

        case wzbgame::message::PositionMoveResponse:
        {
            wzbgame::message::battle::PositionMoveResponse pm;
            p.message().UnpackTo(&pm);
            self->send(buddy, position_move_response_atom_v, pm.result(), pm.position());
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
