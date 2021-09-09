
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

#include	"ServerContents.h"

#include	"atomdef/ZoneMove.h"
#include	"manager/ZoneSupervisor.h"

#include	"LobbyHandler.h"
#include	"../CAF_Atom.h"
#include	"../SingletonInstance.h"
#include	"../ClientState.h"


LobbyHandler::LobbyHandler(caf::event_based_actor* self, User& srcUser)
	: self(self), user(srcUser)
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
			caf::aout(self) << e.what() << std::endl;
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
			caf::aout(self) << e.what() << std::endl;
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
			caf::aout(self) << e.what() << std::endl;
		}

		wzbgame::message::lobby::CharacterSelectResponse response;
		response.set_result(resultValue);
		wzbgame::message::WrappedMessage wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterSelectResponse, response);

		return caf::make_message(send_to_client_atom_v, wrapped.SerializeAsString());
	},

		// �ΰ��� ���� ��û ó��
		[this](ingame_enter_request_atom, std::string stream)
	{
		auto resultValue = wzbgame::type::result::UnknownFailure;

		try
		{
			auto message = ToActorMessageArg<wzbgame::message::lobby::InGameEnterRequest>(stream);

			self->request(ZoneSupervisorInstance->GetActor(), caf::infinite, zone_move::enter_ingame_request_atom_v, user.GetCurrentPlayCharacter()).then(
				[this](zone_move::enter_ingame_response_atom, wzbgame::model::Position startingPosition)
			{
				caf::aout(self) << "LobbyHandler received enter_ingame_response_atom." << std::endl;

				wzbgame::message::lobby::InGameEnterResponse response;
				response.set_result(ResultType::Succeed);
				response.mutable_position()->set_point_x(startingPosition.point_x());
				response.mutable_position()->set_point_y(startingPosition.point_y());
				response.mutable_position()->set_point_z(startingPosition.point_z());
				auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::InGameEnterResponse, response);

				self->send(self, send_to_client_atom_v, wrapped.SerializeAsString());
			}
				);

			resultValue = ResultType::Succeed;
		}
		catch (const WzbContentsException& e)
		{
			resultValue = static_cast<ResultType>(e.ResultCode);
			caf::aout(self) << e.what() << std::endl;
		}

		if (ResultType::Succeed != resultValue)
		{
			wzbgame::message::lobby::InGameEnterResponse failureResponse;
			failureResponse.set_result(resultValue);
			auto failureWrapped = MakeWrappedMessage(wzbgame::message::MessageType::InGameEnterResponse, failureResponse);

			return caf::make_message(send_to_client_atom_v, failureWrapped.SerializeAsString());
		}

		return caf::make_message();
	},
	};
}
