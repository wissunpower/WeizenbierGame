
#include	<algorithm>
#include	<random>

#include	"caf/all.hpp"
#include	"caf/io/all.hpp"

#ifdef CAF_WINDOWS
#	include <WinSock2.h>
#else
#	include <arpa/inet.h>
#endif

CAF_PUSH_WARNINGS
#include	"WeizenbierProto.h"
CAF_POP_WARNINGS

#include	"ServerUtility.h"

#include	"atomdef/ContentsEntity.h"
#include	"model/PlayCharacter.h"

#include	"ZoneState.h"
#include	"../atomdef/ZoneMove.h"
#include	"../atomdef/Battle.h"


ZoneState::ZoneState(caf::event_based_actor* self)
	: self(self)
{
}

caf::behavior ZoneState::make_behavior()
{
	self->attach_functor(
		[this]
	{
		WriteLog(self, "worker " + std::to_string(0) + " down");
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
		// �ΰ��� ���� ��û ó��
		[this](zone_move::enter_ingame_request_atom, PlayCharacter playCharacter)
	{
		WriteLog(self, "Zone received enter_ingame_atom.");
		WriteLog(self, "Entered Character Name : " + playCharacter.GetName());

		wzbgame::model::Position startingPosition;
		startingPosition.set_point_x(0);
		startingPosition.set_point_y(0);
		startingPosition.set_point_z(0);

		auto locatableStartingPosition = GetLocatablePosition(startingPosition);

		playCharacter.SetPosition(locatableStartingPosition);

		std::shared_ptr<PlayCharacter> currentCharacter(new PlayCharacter{ playCharacter });
		gameObjectList.insert(std::make_pair(currentCharacter->GetSN(), currentCharacter));
		gameMoveableObjectList.insert(std::make_pair(currentCharacter->GetSN(), currentCharacter));

		return caf::make_message(zone_move::enter_ingame_response_atom_v, locatableStartingPosition);
	},

		// �ΰ��� ���� ��û ó��
		[this](zone_move::leave_ingame_request_atom, PlayCharacter playCharacter)
	{
		auto gameMoveableObjectIter = gameMoveableObjectList.find(playCharacter.GetSN());

		if (gameMoveableObjectIter != gameMoveableObjectList.end())
		{
			gameMoveableObjectList.erase(gameMoveableObjectIter);
		}

		auto gameObjectIter = gameObjectList.find(playCharacter.GetSN());

		if (gameObjectIter != gameObjectList.end())
		{
			gameObjectList.erase(gameObjectIter);
		}

		return caf::make_message();
	},

		// ĳ���� ��ġ �̵� ��û ó��
		[this](battle::position_move_request_atom, PlayCharacter playCharacter)
	{
		auto resultValue = ResultType::UnknownFailure;
		wzbgame::model::Position nextPosition;

		try
		{
			auto currentCharacter = GetGameMoveableObject(playCharacter.GetSN());
			if (currentCharacter == nullptr)
			{
				throw WZB_CONTENTS_EXCEPTION_RM(ResultType::NotFoundCharacter, "Not Found Character -> Character Name : " + playCharacter.GetName());
			}

			std::vector< std::vector<float> > randomMoveOffset = { {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1} };

			auto seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle(randomMoveOffset.begin(), randomMoveOffset.end(), std::default_random_engine(seed));

			auto positionMap = GetAllObjectPositionMap();
			auto currentPosition = currentCharacter->GetPosition();

			for (const auto& moveOffset : randomMoveOffset)
			{
				nextPosition.set_point_x(currentPosition.point_x() + moveOffset[0]);
				nextPosition.set_point_y(currentPosition.point_y() + moveOffset[1]);
				nextPosition.set_point_z(currentPosition.point_z() + moveOffset[2]);

				auto resultByX = positionMap.find(nextPosition.point_x());
				if (resultByX == positionMap.end())
				{
					break;
				}

				auto resultByY = resultByX->second.find(nextPosition.point_y());
				if (resultByY == resultByX->second.end())
				{
					break;
				}

				auto resultByZ = resultByY->second.find(nextPosition.point_z());
				if (resultByZ == resultByY->second.end() || resultByZ->second == false)
				{
					break;
				}
			}

			if (currentPosition == nextPosition)
			{
				throw WZB_CONTENTS_EXCEPTION_RM(ResultType::NoPositionWhereMoveable,
					"No position where moveable. -> Character Name : " + playCharacter.GetName() + ",  Current Position : " + currentPosition.SerializeAsString());
			}
			else
			{
				currentCharacter->SetPosition(nextPosition);
			}

			resultValue = ResultType::Succeed;
		}
		catch (const WzbContentsException& e)
		{
			resultValue = static_cast<ResultType>(e.ResultCode);
			WriteLog(self, e.what());
		}

		return caf::make_message(battle::position_move_response_atom_v, static_cast<int>(resultValue), nextPosition);
	},
	};
}

std::shared_ptr<ILocatable> ZoneState::GetGameObject(long serialNumber) const
{
	auto gameObject = gameObjectList.find(serialNumber);

	if (gameObject == gameObjectList.end())
	{
		return nullptr;
	}

	return gameObject->second;
}

std::shared_ptr<IMoveable> ZoneState::GetGameMoveableObject(long serialNumber) const
{
	auto gameMoveableObject = gameMoveableObjectList.find(serialNumber);

	if (gameMoveableObject == gameMoveableObjectList.end())
	{
		return nullptr;
	}

	return gameMoveableObject->second;
}

std::map< float, std::map< float, std::map< float, bool > > > ZoneState::GetAllObjectPositionMap() const
{
	std::map< float, std::map< float, std::map< float, bool > > > positionMap;

	// �ٸ� ������ �����ϰ� �ִ� ��ġ�� �����Ѵ�.
	for (auto gameObjectIter = gameObjectList.begin(); gameObjectIter != gameObjectList.end(); ++gameObjectIter)
	{
		if (gameObjectIter->second == nullptr)
		{
			continue;
		}

		const auto& currentPosition = gameObjectIter->second->GetPosition();

		positionMap[currentPosition.point_x()][currentPosition.point_y()][currentPosition.point_z()] = true;
	}

	return positionMap;
}

wzbgame::model::Position ZoneState::GetLocatablePosition(const wzbgame::model::Position& src) const
{
	auto positionMap = GetAllObjectPositionMap();

	auto dest = src;
	float offsetX = 0;

	// src ��ġ���� ���� ����� �� �ڸ��� ã�´�.
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

		// X��ǥ�� �ٲٸ鼭 ������ �� ��ġ�� ã�´�.
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
