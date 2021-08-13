#pragma once


#include	"../interface/IMessageHandler.h"


class User;


class LoginHandler : public IMessageHandler
{

public:
	LoginHandler(User& srcUser);
	virtual ~LoginHandler() = default;

	caf::message_handler GetMessageHandler() const override;

private:
	User& user;

};
