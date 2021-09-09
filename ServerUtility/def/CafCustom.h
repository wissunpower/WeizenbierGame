#pragma once


#include	"caf/fwd.hpp"


namespace caf
{
	constexpr caf::type_id_t custom_type_id_default_offset						=		0;

	constexpr caf::type_id_t custom_type_id_serverside_offset					=	10000;
	constexpr caf::type_id_t custom_type_id_serverside_contentsentity_offset	=	10000;
	constexpr caf::type_id_t custom_type_id_serverside_zonemove_offset			=	11000;
	constexpr caf::type_id_t custom_type_id_serverside_battle_offset			=	12000;
}
