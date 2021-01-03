#pragma once

#include "Player.h"
#include "StartingRoom1111.h"
#include "HallwayVertical1010.h"
#include "HallwayHorizontal0101.h"
#include "TSplit1101.h"
#include "TSplit1110.h"
#include "TSplit0111.h"
#include "TSplit1011.h"
#include "Corner1100.h"
#include "Corner0110.h"
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