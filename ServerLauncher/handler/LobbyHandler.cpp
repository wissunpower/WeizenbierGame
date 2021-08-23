
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

		// ĳ���� ���� ��û ó��
		[this](character_create_request_atom, std::string stream)
	{
		auto resultValue = wzbgame::type::result::UnknownFailure;

		try
		{
			auto message = ToActorMessageArg<wzbgame::message::lobby::CharacterCreateRequest>(stream);

			// TODO : ĳ���� ���̵� �ߺ� Ȯ��
			
			user.CreatePlayCharacter(message.character_id());

			resultValue = wzbgame::type::result::Succeed;
		}
		catch (const WzbContentsException& e)
		{
			resultValue = static_cast<ResultType>(e.ResultCode);
			std::cout << e.what() << std::endl;
		}

		wzbgame::message::lobby::CharacterCreateResponse response;
		response.set_result(resultValue);
		wzbgame::message::WrappedMessage wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterCreateResponse, response);

		return caf::make_message(send_to_client_atom_v, wrapped.SerializeAsString());
	},

		// ĳ���� ���� ��û ó��
		[this](character_delete_request_atom, std::string stream)
	{
		auto resultValue = wzbgame::type::result::UnknownFailure;

		try
		{
			auto message = ToActorMessageArg<wzbgame::message::lobby::CharacterDeleteRequest>(stream);

			user.DeletePlayCharacter(message.character_id());
			
			resultValue = wzbgame::type::result::Succeed;
		}
		catch (const WzbContentsException& e)
		{
			resultValue = static_cast<ResultType>(e.ResultCode);
			std::cout << e.what() << std::endl;
		}

		wzbgame::message::lobby::CharacterDeleteResponse response;
		response.set_result(resultValue);
		wzbgame::message::WrappedMessage wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterDeleteResponse, response);

		return caf::make_message(send_to_client_atom_v, wrapped.SerializeAsString());
	},

		// ĳ���� ���� ��û ó��
		[this](character_select_request_atom, std::string stream)
	{
		auto resultValue = wzbgame::type::result::UnknownFailure;

		try
		{
			auto message = ToActorMessageArg<wzbgame::message::lobby::CharacterSelectRequest>(stream);

			user.SelectPlayCharacter(message.character_id());

			resultValue = wzbgame::type::result::Succeed;
		}
		catch (const WzbContentsException & e)
		{
			resultValue = static_cast<ResultType>(e.ResultCode);
			std::cout << e.what() << std::endl;
		}

		wzbgame::message::lobby::CharacterSelectResponse response;
		response.set_result(resultValue);
		wzbgame::message::WrappedMessage wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterSelectResponse, response);

		return caf::make_message(send_to_client_atom_v, wrapped.SerializeAsString());
	},
	};
}
