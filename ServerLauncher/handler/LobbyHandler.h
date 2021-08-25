#pragma once


#include	"../interface/IMessageHandler.h"


class User;


class LobbyHandler : public IMessageHandler
{

public:
	LobbyHandler(caf::event_based_actor* self, User& srcUser);
	virtual ~LobbyHandler() = default;

	caf::message_handler GetMessageHandler() const override;

private:

	caf::event_based_actor* self;

	User& user;

};
