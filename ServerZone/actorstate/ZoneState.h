#pragma once


#include	<map>

#include	"caf/event_based_actor.hpp"

#include	"interface/ILocatable.h"


class ZoneState
{

public:

	ZoneState(caf::event_based_actor* self);

	caf::behavior make_behavior();

	static inline const char* name = "ZoneState";


public:

	std::shared_ptr<ILocatable> GetGameObject(long serialNumber) const;
	std::shared_ptr<IMoveable> GetGameMoveableObject(long serialNumber) const;

	std::map< float, std::map< float, std::map< float, bool > > > GetAllObjectPositionMap() const;

	// src 을 중심으로 선점 가능한(비어있는 공간) 위치를 검색한다.
	wzbgame::model::Position GetLocatablePosition(const wzbgame::model::Position& src) const;


private:

	caf::event_based_actor* self;

	std::map<long, std::shared_ptr<ILocatable>> gameObjectList;
	std::map<long, std::shared_ptr<IMoveable>> gameMoveableObjectList;

};

using ZoneActor = caf::stateful_actor<ZoneState>;
