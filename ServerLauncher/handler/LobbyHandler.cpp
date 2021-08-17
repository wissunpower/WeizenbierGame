
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

#include	"LobbyHandler.h"
#include	"../CAF_Atom.h"
#include	"../ClientState.h"
#include	"../model/User.h"


LobbyHandler::LobbyHandler(User& srcUser)
	: user(srcUser)
{
	;
}

caf::message_handler LobbyHandler::GetMessageHandler() const
{
	return caf::message_handler{
		[this](character_create_request_atom, std::string stream)
	{
		auto message = ToActorMessageArg<wzbgame::message::lobby::CharacterCreateRequest>(stream);


		// TODO


		wzbgame::message::lobby::CharacterCreateResponse response;
		response.set_result(wzbgame::type::result::Succeed);
		wzbgame::message::WrappedMessage wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterCreateResponse, response);

		return caf::make_message(send_to_client_atom_v, wrapped.SerializeAsString());
	},
		[this](character_delete_request_atom, std::string stream)
	{
		auto message = ToActorMessageArg<wzbgame::message::lobby::CharacterDeleteRequest>(stream);


		// TODO


		wzbgame::message::lobby::CharacterDeleteResponse response;
		response.set_result(wzbgame::type::result::Succeed);
		wzbgame::message::WrappedMessage wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterDeleteResponse, response);

		return caf::make_message(send_to_client_atom_v, wrapped.SerializeAsString());
	},
		[this](character_select_request_atom, std::string stream)
	{
		auto message = ToActorMessageArg<wzbgame::message::lobby::CharacterSelectRequest>(stream);


		// TODO


		wzbgame::message::lobby::CharacterSelectResponse response;
		response.set_result(wzbgame::type::result::Succeed);
		wzbgame::message::WrappedMessage wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterSelectResponse, response);

		return caf::make_message(send_to_client_atom_v, wrapped.SerializeAsString());
	},
	};
}