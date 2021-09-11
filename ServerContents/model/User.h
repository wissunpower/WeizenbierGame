#pragma once


#include	"../pch.h"

#include	<string>
#include	<map>

#include	"WeizenbierProto.h"

#include	"PlayCharacter.h"


class DECLSPEC User
{

public:
	User();

	ResultType CreatePlayCharacter(const long serialNumber, const std::string& characterName);
	ResultType DeletePlayCharacter(const std::string& characterName);

	PlayCharacter& SelectPlayCharacter(const std::string& characterName);
	PlayCharacter& GetCurrentPlayCharacter() const;

public:

	std::string GetAccountID() const
	{
		return accountID;
	}

	void SetAccountID(const std::string& arg)
	{
		accountID = arg;
	}


private:

	std::string accountID;

	// < PlayCharacter.name, PlayCharacter object >
	std::map<std::string, PlayCharacter> _playCharacterList;

	std::map<std::string, PlayCharacter>::iterator _selectedCharacterIter;

};
