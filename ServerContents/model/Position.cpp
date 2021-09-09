
#include	"caf/all.hpp"

#include	"Position.h"


bool operator==(const wzbgame::model::Position& left, const wzbgame::model::Position& right)
{
	return left.point_x() == right.point_x() && left.point_y() == right.point_y() && left.point_z() == right.point_z();
}

std::ostream& operator<<(std::ostream& os, const wzbgame::model::Position& position)
{
	return os << "[ point_x : " << position.point_x() << ", point_y : " << position.point_y() << ", point_z : " << position.point_z() << " ]";
}
