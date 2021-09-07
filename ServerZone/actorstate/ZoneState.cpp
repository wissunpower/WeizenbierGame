
#include	"caf/all.hpp"

#include	"atomdef/ContentsEntity.h"
#include	"model/PlayCharacter.h"

#include	"ZoneState.h"
#include	"../atomdef/ZoneMove.h"


ZoneState::ZoneState(caf::event_based_actor* self)
	: self(self)
{
}

caf::behavior ZoneState::make_behavior()
{
	self->attach_functor(
		[this]
	{
		caf::aout(self) << "worker " << 0 << " down" << std::endl;
	}
	);

	return {
		[](int x, int y)
	{
		if (x % 2 == 1 || y % 2 == 1)
		{
			throw std::runtime_error("I don't do odd numbers!");
		}

		return x + y;
	},
		[this](zone_move::enter_ingame_request_atom, PlayCharacter playCharacter)
	{
		caf::aout(self) << "Zone received enter_ingame_atom." << std::endl;
		caf::aout(self) << "Entered Character Name : " << playCharacter.GetName() << std::endl;

		wzbgame::model::Position startingPosition;
		startingPosition.set_point_x(0);
		startingPosition.set_point_y(0);
		startingPosition.set_point_z(0);

		auto locatableStartingPosition = GetLocatablePosition(startingPosition);

		playCharacter.SetPosition(locatableStartingPosition);

		std::shared_ptr<ILocatable> currentCharacter(new PlayCharacter{ playCharacter });
		gameObjectList.push_back(currentCharacter);

		return caf::make_message(zone_move::enter_ingame_response_atom_v, locatableStartingPosition);
	},
	};
}

wzbgame::model::Position ZoneState::GetLocatablePosition(const wzbgame::model::Position& src) const
{
	std::map< float, std::map< float, std::map< float, bool > > > positionMap;

	// 다른 대상들이 선점하고 있는 위치를 취합한다.
	for (auto gameObjectIter = gameObjectList.begin(); gameObjectIter != gameObjectList.end(); ++gameObjectIter)
	{
		if (gameObjectIter->get() == nullptr)
		{
			continue;
		}

		const auto& currentPosition = gameObjectIter->get()->GetPosition();

		positionMap[ currentPosition.point_x() ][ currentPosition.point_y() ][ currentPosition.point_z() ] = true;
	}

	auto dest = src;
	float offsetX = 0;

	// src 위치에서 가장 가까운 빈 자리를 찾는다.
	while (true)
	{
		auto resultByX = positionMap.find(dest.point_x());
		if (resultByX == positionMap.end())
		{
			break;
		}

		auto resultByY = resultByX->second.find(dest.point_y());
		if (resultByY == resultByX->second.end())
		{
			break;
		}

		auto resultByZ = resultByY->second.find(dest.point_z());
		if (resultByZ == resultByY->second.end() || resultByZ->second == false)
		{
			break;
		}

		// X좌표만 바꾸면서 인접한 빈 위치를 찾는다.
		if (offsetX > 0)
		{
			offsetX *= (-1);
		}
		else
		{
			offsetX = std::abs(offsetX) + 1;
		}

		dest.set_point_x(src.point_x() + offsetX);
	}

	return dest;
}
