#pragma once


#include	<string>


class User
{

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

};
