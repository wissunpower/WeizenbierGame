
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
		startingPosition.set_point_x(21);
		startingPosition.set_point_y(9);
		startingPosition.set_point_z(6);

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
	return src;
}
