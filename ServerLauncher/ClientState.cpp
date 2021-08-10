
#include	"caf/all.hpp"
#include	"caf/io/all.hpp"

#ifdef CAF_WINDOWS
#	include <WinSock2.h>
#else
#	include <arpa/inet.h>
#endif

CAF_PUSH_WARNINGS
#include "WeizenbierProto.h"
CAF_POP_WARNINGS

#include	"ServerUtility.h"

#include	"ClientState.h"
#include	"CAF_Atom.h"


ClientState::ClientState()
{
	// nop
}

caf::behavior ClientState::make_behavior()
{
	return {
		[this](chat_request_atom, std::string stream)
	{
		auto message = ToActorMessageArg<wzbgame::message::chat::ChatRequest>(stream);
		auto chatMessage = message.message();

		std::cout << "'response' " << chatMessage << std::endl;

		wzbgame::message::chat::ChatResponse response;
		response.set_message(chatMessage);
		wzbgame::message::WrappedMessage responseWrapped = MakeWrappedMessage(wzbgame::message::MessageType::ChatResponse, response);

		wzbgame::message::chat::ChatNotification notification;
		//notification.set_name(name);
		notification.set_message(chatMessage);
		wzbgame::message::WrappedMessage notificationWrapped = MakeWrappedMessage(wzbgame::message::MessageType::ChatNotification, notification);

		return caf::make_message(send_and_broadcast_atom_v, responseWrapped.SerializeAsString(), notificationWrapped.SerializeAsString());
	},
		[this](login_request_atom, std::string stream)
	{
		auto message = ToActorMessageArg<wzbgame::message::login::LoginRequest>(stream);

		std::cout << "login account id : " << message.account_id() << std::endl;

		wzbgame::message::login::LoginResponse response;
		response.set_result(wzbgame::type::result::Succeed);
		wzbgame::message::WrappedMessage wrapped = MakeWrappedMessage(wzbgame::message::MessageType::LoginResponse, response);

		return caf::make_message(send_to_client_atom_v, wrapped.SerializeAsString());
	},
	};
}
