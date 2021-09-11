#pragma once


#include	"../pch.h"

#include	"caf/event_based_actor.hpp"


class DECLSPEC UniqueKeyGeneratorState
{

public:

	UniqueKeyGeneratorState(caf::event_based_actor* self);

	caf::behavior make_behavior();

	static inline const char* name = "UniqueKeyGeneratorState";


private:

	caf::event_based_actor* self;

	long lastIssuedKey;

};

using UniqueKeyGeneratorActor = caf::stateful_actor< UniqueKeyGeneratorState>;


class DECLSPEC UniqueKeyGenerator
{

public:

	void SetActor(const caf::actor& actor)
	{
		_actor = std::move(actor);
	}

	const caf::actor& GetActor()
	{
		return _actor;
	}


private:

	caf::actor _actor;

};
