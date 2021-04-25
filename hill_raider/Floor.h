#pragma once

#include "player.h"
#include "crossRoad1111.h"
#include "hallwayVertical1010.h"
#include "hallwayHorizontal0101.h"
#include "tSplit1101.h"
#include "tSplit1110.h"
#include "tSplit0111.h"
#include "tSplit1011.h"
#include "corner1100.h"
#include "corner0110.h"
#include "corner0011.h"
#include "corner1001.h"
#include "deadEnd1000.h"
#include "deadEnd0100.h"
#include "deadEnd0010.h"
#include "deadEnd0001.h"
#include "aStar.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This class contains the floor map for the game. It
	// can be used to keep track of and update the players
	// position in the ant hill.
	// --------------------------------------------------
	class Floor
	{
	private:
		Room* m_FloorMap[9][8];
		int m_CurrentRoom[2];

	public:
		Floor();
		Room* GetCurrentRoom();
		void MoveToNextRoom(Direction direction);
		~Floor();
	};
}