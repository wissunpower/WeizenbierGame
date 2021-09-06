#pragma once


#include	"caf/event_based_actor.hpp"

#include	"interface/ILocatable.h"


class ZoneState
{

public:

	ZoneState(caf::event_based_actor* self);

	caf::behavior make_behavior();

	static inline const char* name = "ZoneState";


public:

	// src �� �߽����� ���� ������(����ִ� ����) ��ġ�� �˻��Ѵ�.
	wzbgame::model::Position GetLocatablePosition(const wzbgame::model::Position& src) const;


private:

	caf::event_based_actor* self;

	std::vector<std::shared_ptr<ILocatable>> gameObjectList;

};

using ZoneActor = caf::stateful_actor<ZoneState>;
