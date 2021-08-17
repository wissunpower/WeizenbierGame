#pragma once


#include	"../interface/IMessageHandler.h"


class User;


class LobbyHandler : public IMessageHandler
{

public:
	LobbyHandler(User& srcUser);
	virtual ~LobbyHandler() = default;

	caf::message_handler GetMessageHandler() const override;

private:
	User& user;

};
