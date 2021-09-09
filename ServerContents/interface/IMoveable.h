#pragma once


#include	"ILocatable.h"


class IMoveable : public ILocatable
{

public:
	virtual void SetPosition(const wzbgame::model::Position& arg) = 0;

};
