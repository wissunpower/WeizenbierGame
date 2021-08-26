
#include	"caf/all.hpp"

#include	"ZoneSupervisor.h"

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
	};
}
