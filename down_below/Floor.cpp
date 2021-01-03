#include "Floor.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Floor::Floor()
	{
		for (int y = 0; y < ((sizeof(floorMap) / sizeof(Room*)) / (sizeof(floorMap[y]) / sizeof(Room*))); y++) {
			for (int x = 0; x < (sizeof(floorMap[y]) / sizeof(Room*)); x++) {
				floorMap[x][y] = nullptr;
			}
		}

		floorMap[1][1] = new StartingRoom1111();
		floorMap[1][0] = new TSplit0111();
		floorMap[0][1] = new TSplit1110();
		floorMap[1][2] = new TSplit1101();
		floorMap[2][1] = new TSplit1011();
		floorMap[0][2] = new Corner1100();
		floorMap[0][0] = new Corner0110();
		floorMap[2][0] = new Corner0011();
		floorMap[2][2] = new Corner1001();

		currentRoom[0] = 1;
		currentRoom[1] = 1;

		AStar::GetIntance()->SetNodeMap(floorMap[currentRoom[0]][currentRoom[1]]->GetTileMap());
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
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Floor::~Floor()
	{
		for (int y = 0; y < ((sizeof(floorMap) / sizeof(Room*)) / (sizeof(floorMap[y]) / sizeof(Room*))); y++) {
			for (int x = 0; x < (sizeof(floorMap[y]) / sizeof(Room*)); x++) {
				if (floorMap[x][y] != nullptr) {
					delete floorMap[x][y];
					floorMap[x][y] = nullptr;
				}
			}
		}
	}
}