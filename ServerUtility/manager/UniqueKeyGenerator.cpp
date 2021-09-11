
#include	"caf/all.hpp"

CAF_PUSH_WARNINGS
#include	"WeizenbierProto.h"
CAF_POP_WARNINGS

#include	"UniqueKeyGenerator.h"

#include	"../def/atom/Certification.h"


UniqueKeyGeneratorState::UniqueKeyGeneratorState(caf::event_based_actor* self)
	: self(self)
	, lastIssuedKey(0)
{
}

caf::behavior UniqueKeyGeneratorState::make_behavior()
{
	return {
		[this](certification::issue_uniquekey_request_atom)
	{
		auto resultValue = ResultType::Succeed;

		return caf::make_message(certification::issue_uniquekey_response_atom_v, static_cast<int>(resultValue), ++lastIssuedKey);
	},
	};
}
