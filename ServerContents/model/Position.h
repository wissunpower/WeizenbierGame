#pragma once


#include	<iostream>

#include	"../pch.h"

#include	"model.pb.h"


//struct DECLSPEC Position
//{
//	float pointX;
//	float pointY;
//	float pointZ;
//};


bool DECLSPEC operator==(const wzbgame::model::Position& left, const wzbgame::model::Position& right);
std::ostream& operator<<(std::ostream& os, const wzbgame::model::Position& position);


namespace caf
{
	template <>
	struct inspector_access<wzbgame::model::Position> : inspector_access_base<wzbgame::model::Position>
	{
		template <typename Inspector>
		static bool apply(Inspector& f, wzbgame::model::Position& src)
		{
			//return f.object(src).fields(f.field("pointX", src.point_x()),
			//							f.field("pointY", src.point_y()),
			//							f.field("pointZ", src.point_z()));

			return true;
		}
	};
}
