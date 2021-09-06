#pragma once


#include	"../pch.h"

#include	<string>

#include	"../interface/IMoveable.h"
#include	"Position.h"


class DECLSPEC PlayCharacter : public IMoveable
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

	wzbgame::model::Position GetPosition() const override
	{
		return position;
	}

	void SetPosition(const wzbgame::model::Position& arg)
	{
		position = arg;
	}

private:

	std::string name;
	wzbgame::model::Position position;

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
