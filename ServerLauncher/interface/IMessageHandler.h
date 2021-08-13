#pragma once


#include	"caf/message_handler.hpp"


class IMessageHandler
{

public:
	virtual caf::message_handler GetMessageHandler() const = 0;

};
