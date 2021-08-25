
#include	"caf/all.hpp"
#include	"caf/io/all.hpp"

#ifdef CAF_WINDOWS
#	include <WinSock2.h>
#else
#	include <arpa/inet.h>
#endif

CAF_PUSH_WARNINGS
#include "WeizenbierProto.h"
CAF_POP_WARNINGS

#include	"ServerUtility.h"

#include	"ClientState.h"
#include	"CAF_Atom.h"


ClientState::ClientState(caf::event_based_actor* self)
	: self(self)
	, user()
	, loginHandler(self, user)
	, chatHandler(self, user)
	, lobbyHandler(self, user)
{
	// nop
}

ClientState::~ClientState()
{
	caf::aout(self) << "destroy ClientState" << std::endl;
}

caf::behavior ClientState::make_behavior()
{
	auto handlerList =
		caf::message_handler{ loginHandler.GetMessageHandler() }
		.or_else(chatHandler.GetMessageHandler())
		.or_else(lobbyHandler.GetMessageHandler());

	return handlerList;
}
