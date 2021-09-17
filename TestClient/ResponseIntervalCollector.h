#pragma once


#include	"caf/event_based_actor.hpp"


class ResponseIntervalCollectorState
{

public:

	ResponseIntervalCollectorState(caf::event_based_actor* self);

	caf::behavior make_behavior();

	static inline const char* name = "ResponseIntervalCollectorState";


private:

	caf::event_based_actor* self;

	std::map<int, std::tuple<int, std::chrono::milliseconds::rep> > statisticsMap;

};

using ResponseIntervalCollectorActor = caf::stateful_actor<ResponseIntervalCollectorState>;


class ResponseIntervalCollector
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