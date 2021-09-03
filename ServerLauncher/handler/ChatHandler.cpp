
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

#include	"model/User.h"

#include	"ChatHandler.h"
#include	"../CAF_Atom.h"


ChatHandler::ChatHandler(caf::event_based_actor* self, User& srcUser)
	: self(self), user(srcUser)
{
	;
}

caf::message_handler ChatHandler::GetMessageHandler() const
{
	return caf::message_handler{
		[this](chat_request_atom, std::string stream)
	{
		auto message = ToActorMessageArg<wzbgame::message::chat::ChatRequest>(stream);
		auto chatMessage = message.message();

		caf::aout(self) << "'response' " << chatMessage << std::endl;

		wzbgame::message::chat::ChatResponse response;
		response.set_message(chatMessage);
		wzbgame::message::WrappedMessage responseWrapped = MakeWrappedMessage(wzbgame::message::MessageType::ChatResponse, response);

		wzbgame::message::chat::ChatNotification notification;
		notification.set_name(user.GetAccountID());
		notification.set_message(chatMessage);
		wzbgame::message::WrappedMessage notificationWrapped = MakeWrappedMessage(wzbgame::message::MessageType::ChatNotification, notification);

		return caf::make_message(send_and_broadcast_atom_v, responseWrapped.SerializeAsString(), notificationWrapped.SerializeAsString());
	}
	};
}
