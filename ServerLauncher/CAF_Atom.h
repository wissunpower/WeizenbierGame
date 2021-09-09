#pragma once


#include	"caf/type_id.hpp"
#include	"caf/io/broker.hpp"

CAF_PUSH_WARNINGS
#include	"WeizenbierProto.h"
CAF_POP_WARNINGS

#include	"def/CafCustom.h"


CAF_BEGIN_TYPE_ID_BLOCK(server_launcher, (first_custom_type_id + custom_type_id_default_offset))

CAF_ADD_ATOM(server_launcher, send_to_client_atom)
CAF_ADD_ATOM(server_launcher, broadcast_atom)
CAF_ADD_ATOM(server_launcher, broadcast_notification_atom)
CAF_ADD_ATOM(server_launcher, send_and_broadcast_atom)

CAF_ADD_ATOM(server_launcher, chat_request_atom)

CAF_ADD_ATOM(server_launcher, login_request_atom)

CAF_ADD_ATOM(server_launcher, character_create_request_atom)
CAF_ADD_ATOM(server_launcher, character_delete_request_atom)
CAF_ADD_ATOM(server_launcher, character_select_request_atom)
CAF_ADD_ATOM(server_launcher, ingame_enter_request_atom)

CAF_ADD_ATOM(server_launcher, position_move_request_atom)

CAF_END_TYPE_ID_BLOCK(server_launcher)


bool SendContentsMessage(caf::io::broker* broker, const caf::actor& dest,
	const wzbgame::message::WrappedMessage& message);