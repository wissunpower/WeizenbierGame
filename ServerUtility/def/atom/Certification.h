#pragma once


#include	"caf/type_id.hpp"

#include	"def/CafCustom.h"


CAF_BEGIN_TYPE_ID_BLOCK(certification, (first_custom_type_id + custom_type_id_serverside_certification_offset))

CAF_ADD_ATOM(certification, certification, issue_uniquekey_request_atom)
CAF_ADD_ATOM(certification, certification, issue_uniquekey_response_atom)

CAF_END_TYPE_ID_BLOCK(certification)
