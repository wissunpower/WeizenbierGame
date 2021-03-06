
#include	"caf/all.hpp"
#include	"caf/io/all.hpp"

#ifdef CAF_WINDOWS
#	include <WinSock2.h>
#else
#	include <arpa/inet.h>
#endif

CAF_PUSH_WARNINGS
#include	"WeizenbierProto.h"
CAF_POP_WARNINGS

#include	"ServerUtility.h"

#include	"ServerContents.h"

#include	"atomdef/ZoneMove.h"
#include	"manager/ZoneSupervisor.h"

#include	"ClientState.h"
#include	"CAF_Atom.h"
#include	"SingletonInstance.h"


ClientState::ClientState(caf::event_based_actor* self, caf::io::connection_handle hdl)
	: self(self), hdl(hdl)
	, user()
	, loginHandler(self, user)
	, chatHandler(self, user)
	, lobbyHandler(self, user)
	, battleHandler(self, user)
{
	// nop
}

ClientState::~ClientState()
{
	if (user.HasSelectedCharacter())
	{
		self->request(ZoneSupervisorInstance->GetActor(), caf::infinite, zone_move::leave_ingame_request_atom_v, user.GetCurrentPlayCharacter());
	}

	WriteLog(self, "destroy ClientState");
}

caf::behavior ClientState::make_behavior()
{
	auto handlerList =
		caf::message_handler{ loginHandler.GetMessageHandler() }
		.or_else(chatHandler.GetMessageHandler())
		.or_else(lobbyHandler.GetMessageHandler())
		.or_else(battleHandler.GetMessageHandler())
		.or_else(caf::message_handler{
		[this](send_to_client_atom, std::string stream)
	{
		self->send(GlobalContextInstance->GetServerActor(), send_to_client_atom_v, hdl, stream);
	},
			});

	return handlerList;
}
