#pragma once


#include	"caf/actor_system_config.hpp"

#include	"../pch.h"


class DECLSPEC ActorSystemConfig : public caf::actor_system_config
{
public:
	uint16_t port = 0;
	std::string host = "localhost";

	ActorSystemConfig()
	{
		opt_group{ custom_options_, "global" }
		.add(port, "port,p", "set port");
	}
};
