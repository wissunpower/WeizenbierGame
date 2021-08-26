#pragma once


#include	"caf/event_based_actor.hpp"


class ZoneState
{

public:

	ZoneState(caf::event_based_actor* self);

	caf::behavior make_behavior();

	static inline const char* name = "ZoneState";


private:

	caf::event_based_actor* self;

};

using ZoneActor = caf::stateful_actor<ZoneState>;
