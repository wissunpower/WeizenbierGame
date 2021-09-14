#pragma once


#include	"caf/event_based_actor.hpp"


class BotState
{

public:

	BotState(caf::event_based_actor* self);
	~BotState();

	caf::behavior make_behavior();

	static inline const char* name = "BotState";


private:

	caf::event_based_actor* self;

	std::string currentCharacterName;

};

using BotActor = caf::stateful_actor<BotState>;
