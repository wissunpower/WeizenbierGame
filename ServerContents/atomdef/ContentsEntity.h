#pragma once


#include	"caf/type_id.hpp"

#include	"def/CafCustom.h"


class PlayCharacter;


CAF_BEGIN_TYPE_ID_BLOCK(contents_entity, (first_custom_type_id + custom_type_id_serverside_contentsentity_offset))

CAF_ADD_TYPE_ID(contents_entity, (PlayCharacter))

CAF_END_TYPE_ID_BLOCK(contents_entity)
