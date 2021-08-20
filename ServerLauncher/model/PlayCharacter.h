#pragma once


#include	<string>


class PlayCharacter
{

public:

	std::string GetName() const
	{
		return name;
	}

	void SetName(const std::string& arg)
	{
		name = arg;
	}


private:

	std::string name;

};