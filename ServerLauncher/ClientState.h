#pragma once


#include	"caf/behavior.hpp"


class ClientState
{

public:

	explicit ClientState();

	caf::behavior make_behavior();

	static inline const char* name = "ClientState";

private:
	std::string accountID;

};

using ClientActor = caf::stateful_actor<ClientState>;
