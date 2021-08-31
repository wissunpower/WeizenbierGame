
#include	"caf/all.hpp"

#include	"ZoneState.h"
#include	"../atomdef/ZoneMove.h"


ZoneState::ZoneState(caf::event_based_actor* self)
	: self(self)
{
}

caf::behavior ZoneState::make_behavior()
{
	self->attach_functor(
		[this]
	{
		caf::aout(self) << "worker " << 0 << " down" << std::endl;
	}
	);

	return {
		[](int x, int y)
	{
		if (x % 2 == 1 || y % 2 == 1)
		{
			throw std::runtime_error("I don't do odd numbers!");
		}

		return x + y;
	},
		[this](zone_move::enter_ingame_request_atom)
	{
		caf::aout(self) << "Zone received enter_ingame_atom." << std::endl;

		return caf::make_message(zone_move::enter_ingame_response_atom_v);
	},
	};
}
