#pragma once


#include	"caf/type_id.hpp"

#include	"def/CafCustom.h"


CAF_BEGIN_TYPE_ID_BLOCK(battle, (first_custom_type_id + custom_type_id_serverside_battle_offset))

CAF_ADD_ATOM(battle, battle, position_move_request_atom)
CAF_ADD_ATOM(battle, battle, position_move_response_atom)

CAF_END_TYPE_ID_BLOCK(battle)
