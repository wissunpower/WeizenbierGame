#pragma once


#include	"caf/type_id.hpp"

#include	"def/CafCustom.h"


CAF_BEGIN_TYPE_ID_BLOCK(zone_move, (first_custom_type_id + custom_type_id_serverside_zonemove_offset))

CAF_ADD_ATOM(zone_move, zone_move, enter_ingame_request_atom)
CAF_ADD_ATOM(zone_move, zone_move, enter_ingame_response_atom)

CAF_ADD_ATOM(zone_move, zone_move, leave_ingame_request_atom)
CAF_ADD_ATOM(zone_move, zone_move, leave_ingame_response_atom)

CAF_END_TYPE_ID_BLOCK(zone_move)
