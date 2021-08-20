
#include	"User.h"

#include	"../ServerUtility/model/exception/WzbContentsException.h"


ResultType User::CreatePlayCharacter(const std::string& characterName)
{
	auto ownedCharacter = _playCharacterList.find(characterName);

	if (ownedCharacter != _playCharacterList.end())
		throw WZB_CONTENTS_EXCEPTION_R(wzbgame::type::result::AlreadyExistCharacter);

	PlayCharacter playCharacter;
	playCharacter.SetName(characterName);

	_playCharacterList.emplace(characterName, playCharacter);

	return ResultType::Succeed;
}

ResultType User::DeletePlayCharacter(const std::string& characterName)
{
	auto ownedCharacter = _playCharacterList.find(characterName);

	if (ownedCharacter == _playCharacterList.end())
		throw WZB_CONTENTS_EXCEPTION_R(wzbgame::type::result::NotFoundCharacter);

	_playCharacterList.erase(ownedCharacter);

	return ResultType::Succeed;
}
