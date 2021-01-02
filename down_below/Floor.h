#pragma once

#include "Player.h"
#include "StartingRoom1111.h"
#include "HallwayVertical1010.h"
#include "HallwayHorizontal0101.h"
#include "AStar.h"

namespace HillRaider
{
	class Floor
	{
	public:
		enum class MoveDirection {UP = 0, RIGHT, DOWN, LEFT};

	private:
		Room* floorMap[3][3];
		int currentRoom[2];

	public:
		Floor();
		Room* GetCurrentRoom();
		void MoveToNextRoom(MoveDirection direction);
		~Floor();
	};
}