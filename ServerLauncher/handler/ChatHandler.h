#pragma once


#include	"../interface/IMessageHandler.h"


class User;


class ChatHandler : public IMessageHandler
{

public:
	ChatHandler(User& srcUser);
	virtual ~ChatHandler() = default;

	caf::message_handler GetMessageHandler() const override;

private:
	User& user;

};
