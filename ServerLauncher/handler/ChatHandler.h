#pragma once


#include	"../interface/IMessageHandler.h"


class User;


class ChatHandler : public IMessageHandler
{

public:
	ChatHandler(caf::event_based_actor* self, User& srcUser);
	virtual ~ChatHandler() = default;

	caf::message_handler GetMessageHandler() const override;

private:

	caf::event_based_actor* self;

	User& user;

};
