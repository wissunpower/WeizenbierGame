
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

#include	"LoginHandler.h"
#include	"../CAF_Atom.h"
#include	"../ClientState.h"


LoginHandler::LoginHandler(caf::event_based_actor* self, User& srcUser)
	: self(self), user(srcUser)
{
	;
}

caf::message_handler LoginHandler::GetMessageHandler() const
{
	return caf::message_handler{
		[this](login_request_atom, std::string stream)
	{
		auto message = ToActorMessageArg<wzbgame::message::login::LoginRequest>(stream);

		caf::aout(self) << "login account id : " << message.account_id() << std::endl;

		user.SetAccountID(message.account_id());

		wzbgame::message::login::LoginResponse response;
		response.set_result(wzbgame::type::result::Succeed);
		wzbgame::message::WrappedMessage wrapped = MakeWrappedMessage(wzbgame::message::MessageType::LoginResponse, response);

		return caf::make_message(send_to_client_atom_v, wrapped.SerializeAsString());
	}
	};
}
