#pragma once


#include	"model.pb.h"


class ILocatable
{

public:
	virtual wzbgame::model::Position GetPosition() const = 0;

};
