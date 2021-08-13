
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
#include	"handler/LoginHandler.h"
#include	"handler/ChatHandler.h"


ClientState::ClientState()
	: user()
	, loginHandler(user)
	, chatHandler(user)
{
	// nop
}

ClientState::~ClientState()
{
	std::cout << "destroy ClientState" << std::endl;
}

caf::behavior ClientState::make_behavior()
{
	auto handlerList = caf::message_handler{ loginHandler.GetMessageHandler() }.or_else(chatHandler.GetMessageHandler());

	return handlerList;
}
