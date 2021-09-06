#pragma once


#include	"../pch.h"

#include	"model.pb.h"


//struct DECLSPEC Position
//{
//	float pointX;
//	float pointY;
//	float pointZ;
//};


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
