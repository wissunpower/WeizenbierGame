#pragma once


#include	"../pch.h"

#include	<string>


class DECLSPEC PlayCharacter
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

namespace caf
{
	template <>
	struct inspector_access<PlayCharacter> : inspector_access_base<PlayCharacter>
	{
		template <typename Inspector>
		static bool apply(Inspector& f, PlayCharacter& src)
		{
			//return f.object(src).fields(f.field("name", src.GetName()));
			return true;
		}
	};
}
