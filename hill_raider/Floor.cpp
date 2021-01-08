#include "Floor.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Floor::Floor()
	{
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 9; x++) {
				floorMap[x][y] = nullptr;
			}
		}

		floorMap[1][0] = new DeadEnd0010();
		floorMap[0][1] = new DeadEnd0100();
		floorMap[1][1] = new StartingRoom1111();
		floorMap[2][1] = new HallwayHorizontal0101();
		floorMap[3][1] = new Corner0011();
		floorMap[7][1] = new DeadEnd0010();
		floorMap[1][2] = new HallwayVertical1010();
		floorMap[3][2] = new HallwayVertical1010();
		floorMap[5][2] = new Corner0110();
		floorMap[6][2] = new TSplit0111();
		floorMap[7][2] = new Corner1001();
		floorMap[0][3] = new DeadEnd0100();
		floorMap[1][3] = new StartingRoom1111();
		floorMap[2][3] = new HallwayHorizontal0101();
		floorMap[3][3] = new StartingRoom1111();
		floorMap[4][3] = new HallwayHorizontal0101();
		floorMap[5][3] = new TSplit1011();
		floorMap[6][3] = new HallwayVertical1010();
		floorMap[1][4] = new HallwayVertical1010();
		floorMap[2][4] = new Corner0110();
		floorMap[3][4] = new TSplit1011();
		floorMap[5][4] = new HallwayVertical1010();
		floorMap[6][4] = new Corner1100();
		floorMap[7][4] = new TSplit0111();
		floorMap[8][4] = new DeadEnd0001();
		floorMap[1][5] = new HallwayVertical1010();
		floorMap[2][5] = new HallwayVertical1010();
		floorMap[3][5] = new Corner1100();
		floorMap[4][5] = new HallwayHorizontal0101();
		floorMap[5][5] = new TSplit1101();
		floorMap[6][5] = new HallwayHorizontal0101();
		floorMap[7][5] = new Corner1001();
		floorMap[1][6] = new Corner1100();
		floorMap[2][6] = new TSplit1011();
		floorMap[2][7] = new DeadEnd1000();

		currentRoom[0] = 3;
		currentRoom[1] = 3;

		AStar::GetIntance()->SetNodeMap(floorMap[currentRoom[0]][currentRoom[1]]->GetTileMap());
		AStar::GetIntance()->SetEntitiesListReference(floorMap[currentRoom[0]][currentRoom[1]]->GetEnemyListReference());
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Room* Floor::GetCurrentRoom()
	{
		return floorMap[currentRoom[0]][currentRoom[1]];
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Floor::MoveToNextRoom(MoveDirection direction)
	{
		switch (direction)
		{
		case MoveDirection::UP:
			--currentRoom[1];
			break;

		case MoveDirection::RIGHT:
			++currentRoom[0];
			break;

		case MoveDirection::DOWN:
			++currentRoom[1];
			break;

		case MoveDirection::LEFT:
			--currentRoom[0];
			break;
		}

		AStar::GetIntance()->SetNodeMap(floorMap[currentRoom[0]][currentRoom[1]]->GetTileMap());
		AStar::GetIntance()->SetEntitiesListReference(floorMap[currentRoom[0]][currentRoom[1]]->GetEnemyListReference());
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Floor::~Floor()
	{
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 9; x++) {
				if (floorMap[x][y] != nullptr) {
					delete floorMap[x][y];
					floorMap[x][y] = nullptr;
				}
			}
		}
	}
}