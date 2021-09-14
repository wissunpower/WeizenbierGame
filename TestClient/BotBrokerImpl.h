#pragma once


#include	"caf/io/broker.hpp"


void BotBrokerHandler(caf::io::broker* self, caf::io::connection_handle hdl, const caf::actor& buddy);
