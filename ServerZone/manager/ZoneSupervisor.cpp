
#include	"caf/all.hpp"

#include	"ZoneSupervisor.h"

#include	"patterns/Singleton.h"

#include	"atomdef/ContentsEntity.h"
#include	"model/PlayCharacter.h"

#include	"../atomdef/ZoneMove.h"
#include	"../atomdef/Battle.h"
#include	"../actorstate/ZoneState.h"


ZoneSupervisorState::ZoneSupervisorState(caf::event_based_actor* self)
	: self(self)
{
}

caf::behavior ZoneSupervisorState::make_behavior()
{
	zoneSet.emplace_back(self->spawn<ZoneActor, caf::linked>());

	self->set_exit_handler([this](const caf::exit_msg& msg)
	{
		auto is_source = [&msg](const auto& hdl)
		{
			return hdl == msg.source;
		};

		auto i = std::find_if(zoneSet.begin(), zoneSet.end(), is_source);

		if (i != zoneSet.end())
		{
			auto n = std::distance(zoneSet.begin(), i);
			caf::aout(self) << "lost a zone " << n << " -> spawn replacement" << std::endl;
			*i = self->spawn<ZoneActor, caf::linked>();
		}
	});

	return {
		[this](int x, int y)
	{
		self->delegate(zoneSet[index], x, y);
		index = (index + 1) % zoneSet.size();
	},
		[this](zone_move::enter_ingame_request_atom, PlayCharacter playCharacter)
	{
		caf::aout(self) << "Zone Supervisor received enter_ingame_atom." << std::endl;
		self->delegate(zoneSet[index], zone_move::enter_ingame_request_atom_v, playCharacter);
	},
		[this](battle::position_move_request_atom, PlayCharacter playCharacter)
	{
		self->delegate(zoneSet[index], battle::position_move_request_atom_v, playCharacter);
	},
	};
}
