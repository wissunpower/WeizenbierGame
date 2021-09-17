
#include    "caf/all.hpp"

CAF_PUSH_WARNINGS
#include    "WeizenbierProto.h"
CAF_POP_WARNINGS

#include	"ResponseIntervalCollector.h"

#include	"AtomDef.h"


ResponseIntervalCollectorState::ResponseIntervalCollectorState(caf::event_based_actor* self)
	: self(self)
{
}

caf::behavior ResponseIntervalCollectorState::make_behavior()
{
	return {
		[=](add_responseinterval_atom, int responseType, std::chrono::milliseconds::rep interval)
	{
		++std::get<0>(statisticsMap[responseType]);
		std::get<1>(statisticsMap[responseType]) += interval;
	},
		[=](show_responseintervalresult)
	{
		caf::aout(self) << "\n*** Total Statistics ***" << std::endl;

		for (auto statisticsIter : statisticsMap)
		{
			if (std::get<0>(statisticsIter.second) <= 0)
			{
				continue;
			}

			std::string responseType;

			switch (statisticsIter.first)
			{

			case wzbgame::message::MessageType::LoginRequest:
				responseType = "LoginRequest";
				break;

			case wzbgame::message::MessageType::CharacterCreateRequest:
				responseType = "CharacterCreateRequest";
				break;

			case wzbgame::message::MessageType::CharacterSelectRequest:
				responseType = "CharacterSelectRequest";
				break;

			case wzbgame::message::MessageType::InGameEnterRequest:
				responseType = "InGameEnterRequest";
				break;

			case wzbgame::message::MessageType::PositionMoveRequest:
				responseType = "PositionMoveRequest";
				break;

			}

			caf::aout(self) << responseType << " -> Aver Milli Sec : " << std::get<1>(statisticsIter.second) / std::get<0>(statisticsIter.second)
				<< ",  Count : " << std::get<0>(statisticsIter.second) << std::endl;
		}

		self->quit();
	},
	};
}
