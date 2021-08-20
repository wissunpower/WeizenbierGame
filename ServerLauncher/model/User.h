#pragma once


#include	<string>
#include	<map>

#include	"WeizenbierProto.h"

#include	"PlayCharacter.h"


class User
{

public:

	ResultType CreatePlayCharacter(const std::string& characterName);


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
	std::map<std::string, PlayCharacter> playCharacterList;

};
