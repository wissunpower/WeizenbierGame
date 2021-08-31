#pragma once


#include	<caf/actor.hpp>
#include	<caf/io/broker.hpp>


class ZoneSupervisor;

extern ZoneSupervisor* ZoneSupervisorInstance;


class GlobalContext
{
public:
	int RegisterActor(caf::io::connection_handle hdl, const caf::actor& actor)
	{
		m_actorMap.emplace(std::make_pair(hdl, actor));
		return 0;
	}

	std::map<caf::io::connection_handle, caf::actor>& GetActorMap()
	{
		return m_actorMap;
	}

	void SetServerActor(const caf::actor& actor)
	{
		serverActor = std::move(actor);
	}

	const caf::actor& GetServerActor()
	{
		return serverActor;
	}

private:
	std::map<caf::io::connection_handle, caf::actor> m_actorMap;
	caf::actor serverActor;
};

extern GlobalContext* GlobalContextInstance;
