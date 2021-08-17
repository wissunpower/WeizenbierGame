#pragma once


#include	"caf/behavior.hpp"

#include	"model/User.h"
#include	"handler/LoginHandler.h"
#include	"handler/ChatHandler.h"
#include	"handler/LobbyHandler.h"


class ClientState
{

public:

	explicit ClientState();
	~ClientState();

	caf::behavior make_behavior();

	static inline const char* name = "ClientState";

public:
	User& GetUser() { return user; }


private:
	LoginHandler loginHandler;
	ChatHandler chatHandler;
	LobbyHandler lobbyHandler;

	User user;

};

using ClientActor = caf::stateful_actor<ClientState>;
