#include "floor.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This contructor is used to set up the floor map for
	// the gameplay.
	// --------------------------------------------------
	Floor::Floor()
	{
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 9; x++) {
				m_FloorMap[x][y] = nullptr;
			}
		}

		m_FloorMap[1][0] = new DeadEnd0010();
		m_FloorMap[0][1] = new DeadEnd0100();
		m_FloorMap[1][1] = new CrossRoad1111();
		m_FloorMap[2][1] = new HallwayHorizontal0101();
		m_FloorMap[3][1] = new Corner0011();
		m_FloorMap[7][1] = new DeadEnd0010();
		m_FloorMap[1][2] = new HallwayVertical1010();
		m_FloorMap[3][2] = new HallwayVertical1010();
		m_FloorMap[5][2] = new Corner0110();
		m_FloorMap[6][2] = new TSplit0111();
		m_FloorMap[7][2] = new Corner1001();
		m_FloorMap[0][3] = new DeadEnd0100();
		m_FloorMap[1][3] = new CrossRoad1111();
		m_FloorMap[2][3] = new HallwayHorizontal0101();
		m_FloorMap[3][3] = new CrossRoad1111();
		m_FloorMap[4][3] = new HallwayHorizontal0101();
		m_FloorMap[5][3] = new TSplit1011();
		m_FloorMap[6][3] = new HallwayVertical1010();
		m_FloorMap[1][4] = new HallwayVertical1010();
		m_FloorMap[2][4] = new Corner0110();
		m_FloorMap[3][4] = new TSplit1011();
		m_FloorMap[5][4] = new HallwayVertical1010();
		m_FloorMap[6][4] = new Corner1100();
		m_FloorMap[7][4] = new TSplit0111();
		m_FloorMap[8][4] = new DeadEnd0001();
		m_FloorMap[1][5] = new HallwayVertical1010();
		m_FloorMap[2][5] = new HallwayVertical1010();
		m_FloorMap[3][5] = new Corner1100();
		m_FloorMap[4][5] = new HallwayHorizontal0101();
		m_FloorMap[5][5] = new TSplit1101();
		m_FloorMap[6][5] = new HallwayHorizontal0101();
		m_FloorMap[7][5] = new Corner1001();
		m_FloorMap[1][6] = new Corner1100();
		m_FloorMap[2][6] = new TSplit1011();
		m_FloorMap[2][7] = new DeadEnd1000();

		m_CurrentRoom[0] = 3;
		m_CurrentRoom[1] = 3;
	}

	// --------------------------------------------------
	// This method is used to get the room which the player
	// is currently in.
	// --------------------------------------------------
	Room* Floor::GetCurrentRoom()
	{
		return m_FloorMap[m_CurrentRoom[0]][m_CurrentRoom[1]];
	}

	// --------------------------------------------------
	// This method is used to move the player to a different
	// room.
	// --------------------------------------------------
	void Floor::MoveToNextRoom(Direction direction)
	{
		switch (direction)
		{
		// Move up one room
		case Direction::UP:
			--m_CurrentRoom[1];
			break;

		// Move right one room
		case Direction::RIGHT:
			++m_CurrentRoom[0];
			break;

		// Move down one room
		case Direction::DOWN:
			++m_CurrentRoom[1];
			break;

		// Move left one room
		case Direction::LEFT:
			--m_CurrentRoom[0];
			break;
		}

		// Update the required for the a* algorithm
		AStar::GetIntance()->SetNodeMap(m_FloorMap[m_CurrentRoom[0]][m_CurrentRoom[1]]->GetTileMap());
		AStar::GetIntance()->SetEntitiesListReference(m_FloorMap[m_CurrentRoom[0]][m_CurrentRoom[1]]->GetEnemyListReference());
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// for the floor map.
	// --------------------------------------------------
	Floor::~Floor()
	{
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 9; x++) {
				if (m_FloorMap[x][y] != nullptr) {
					delete m_FloorMap[x][y];
					m_FloorMap[x][y] = nullptr;
				}
			}
		}
	}
}