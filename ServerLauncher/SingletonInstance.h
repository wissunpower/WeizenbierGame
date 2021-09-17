#pragma once


#include	<caf/actor.hpp>
#include	<caf/io/broker.hpp>


class ZoneSupervisor;

extern ZoneSupervisor* ZoneSupervisorInstance;

class UniqueKeyGenerator;

extern UniqueKeyGenerator* UniqueKeyGeneratorInstance;


class GlobalContext
{
public:
	int RegisterActor(caf::io::connection_handle hdl, const caf::actor& actor)
	{
		auto actorIter = m_actorMap.find(hdl);

		if (actorIter != m_actorMap.end())
		{
			m_actorMap.erase(actorIter);
		}

		m_actorMap.emplace(std::make_pair(hdl, actor));

		return 0;
	}

	int ReleaseActor(caf::io::connection_handle hdl)
	{
		auto actorIter = m_actorMap.find(hdl);

		if (actorIter != m_actorMap.end())
		{
			m_actorMap.erase(hdl);
		}

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
