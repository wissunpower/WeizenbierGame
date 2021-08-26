#pragma once


#include	"../pch.h"

#include	"caf/event_based_actor.hpp"

#include	"patterns/Singleton.h"


class DECLSPEC ZoneSupervisorState
{

public:

	ZoneSupervisorState(caf::event_based_actor* self);

	caf::behavior make_behavior();

	static inline const char* name = "ZoneSupervisorState";


private:

	caf::event_based_actor* self;

	std::vector<caf::actor> zoneSet;

	size_t index = 0;

};

using ZoneSupervisorActor = caf::stateful_actor<ZoneSupervisorState>;



class ZoneSupervisor
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

auto ZoneSupervisorInstance = Singleton<ZoneSupervisor>::Get();
