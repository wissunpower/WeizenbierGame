#pragma once


#include	"../interface/IMessageHandler.h"


class User;


class LoginHandler : public IMessageHandler
{

public:
	LoginHandler(caf::event_based_actor* self, User& srcUser);
	virtual ~LoginHandler() = default;

	caf::message_handler GetMessageHandler() const override;

private:

	caf::event_based_actor* self;

	User& user;

};
