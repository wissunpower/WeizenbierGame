
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

#include	"atomdef/Battle.h"
#include	"manager/ZoneSupervisor.h"

#include	"BattleHandler.h"
#include	"../CAF_Atom.h"
#include	"../SingletonInstance.h"


BattleHandler::BattleHandler(caf::event_based_actor* self, User& srcUser)
	: self(self), user(srcUser)
{
	;
}

caf::message_handler BattleHandler::GetMessageHandler() const
{
	return caf::message_handler{

		// 캐릭터 위치 이동 요청 처리
		[this](position_move_request_atom, std::string stream)
	{
		auto resultValue = ResultType::UnknownFailure;

		try
		{
			auto message = ToActorMessageArg<wzbgame::message::battle::PositionMoveRequest>(stream);

			auto currentCharacter = user.GetCurrentPlayCharacter();

			self->request(ZoneSupervisorInstance->GetActor(), caf::infinite, battle::position_move_request_atom_v, currentCharacter).then(
				[this](battle::position_move_response_atom, int result, wzbgame::model::Position nextPosition)
			{
				WriteLog(self, "BattleHandler received position_move_response_atom.");

				if (result == static_cast<int>(ResultType::Succeed))
				{
					user.GetCurrentPlayCharacter().SetPosition(nextPosition);
				}

				wzbgame::message::battle::PositionMoveResponse response;
				response.set_result(result);
				response.mutable_position()->set_point_x(nextPosition.point_x());
				response.mutable_position()->set_point_y(nextPosition.point_y());
				response.mutable_position()->set_point_z(nextPosition.point_z());
				auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::PositionMoveResponse, response);

				self->send(self, send_to_client_atom_v, wrapped.SerializeAsString());
			}
			);

			resultValue = wzbgame::type::result::Succeed;
		}
		catch (const WzbContentsException& e)
		{
			resultValue = static_cast<ResultType>(e.ResultCode);
			WriteLog(self, e.what());
		}

		if (ResultType::Succeed != resultValue)
		{
			wzbgame::message::battle::PositionMoveResponse failureResponse;
			failureResponse.set_result(resultValue);
			auto failureWrapped = MakeWrappedMessage(wzbgame::message::MessageType::PositionMoveResponse, failureResponse);

			return caf::make_message(send_to_client_atom_v, failureWrapped.SerializeAsString());
		}

		return caf::make_message();
	},
	};
}
