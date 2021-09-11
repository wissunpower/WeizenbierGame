
#include	"caf/all.hpp"

#include	"User.h"

#include	"../ServerUtility/model/exception/WzbContentsException.h"


User::User()
	: _selectedCharacterIter(_playCharacterList.end())
{
}

ResultType User::CreatePlayCharacter(const long serialNumber, const std::string& characterName)
{
	auto ownedCharacter = _playCharacterList.find(characterName);

	if (ownedCharacter != _playCharacterList.end())
		throw WZB_CONTENTS_EXCEPTION_R(wzbgame::type::result::AlreadyExistCharacter);

	PlayCharacter playCharacter;
	playCharacter.SetSN(serialNumber);
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

PlayCharacter& User::SelectPlayCharacter(const std::string& characterName)
{
	auto foundCharacterIter = _playCharacterList.find(characterName);

	if (foundCharacterIter == _playCharacterList.end())
		throw WZB_CONTENTS_EXCEPTION_R(wzbgame::type::result::NotFoundCharacter);

	_selectedCharacterIter = foundCharacterIter;

	return _selectedCharacterIter->second;
}

PlayCharacter& User::GetCurrentPlayCharacter() const
{
	if (_selectedCharacterIter == _playCharacterList.end())
		throw WZB_CONTENTS_EXCEPTION_R(wzbgame::type::result::InvalidCurrentCharacter);

	return _selectedCharacterIter->second;
}
