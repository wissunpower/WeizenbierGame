#pragma once


#include	"../interface/IMessageHandler.h"


class User;


class BattleHandler : public IMessageHandler
{

public:
	BattleHandler(caf::event_based_actor* self, User& srcUser);
	virtual ~BattleHandler() = default;

	caf::message_handler GetMessageHandler() const override;


private:

	caf::event_based_actor* self;

	User& user;

};
