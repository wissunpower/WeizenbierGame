
#include	"User.h"

#include	"../ServerUtility/model/exception/WzbContentsException.h"


ResultType User::CreatePlayCharacter(const std::string& characterName)
{
	auto ownedCharacter = playCharacterList.find(characterName);

	if (ownedCharacter != playCharacterList.end())
		throw WZB_CONTENTS_EXCEPTION_R(wzbgame::type::result::AlreadyExistCharacter);

	PlayCharacter playCharacter;
	playCharacter.SetName(characterName);

	playCharacterList.emplace(characterName, playCharacter);

	return ResultType::Succeed;
}
