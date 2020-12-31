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

		char tilemap0[9][46]{
		"aaxacxacxacxacxacxacxaewacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"beaca ca ca ca ca ca ca ca ca ca ca ca ca afd",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbfsbdxbdxbdxbdxbdxbdxbbx"
		};

		floorMap[1][1] = new Room(new TileMap("assets/gameplay/tile_maps/tile_map.png", tilemap0, 64, 64), std::list<Entity*>{new RagDoll(64 * 4, 64* 4, 150.f, 38, 62)});

		char tilemap1[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca eexca ca ca ca ca ca adx",
		"bcxca ca ca ca ca edxefxebxca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ecxca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbfsbdxbdxbdxbdxbdxbdxbbx"
		};

		floorMap[1][0] = new Room(new TileMap("assets/gameplay/tile_maps/tile_map.png", tilemap1, 64, 64), std::list<Entity*>{});

		char tilemap2[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca eexca ca ca ca ca ca adx",
		"bcxca ca ca ca ca edxefxebxca ca ca ca ca afd",
		"bcxca ca ca ca ca ca ecxca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
		};

		floorMap[0][1] = new Room(new TileMap("assets/gameplay/tile_maps/tile_map.png", tilemap2, 64, 64), std::list<Entity*>{});

		char tilemap3[9][46]{
		"aaxacxacxacxacxacxacxaewacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca eexca ca ca ca ca ca adx",
		"bcxca ca ca ca ca edxefxebxca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ecxca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
		};

		floorMap[1][2] = new Room(new TileMap("assets/gameplay/tile_maps/tile_map.png", tilemap3, 64, 64), std::list<Entity*>{});

		char tilemap4[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca eexca ca ca ca ca ca adx",
		"beaca ca ca ca ca edxefxebxca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ecxca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
		};

		floorMap[2][1] = new Room(new TileMap("assets/gameplay/tile_maps/tile_map.png", tilemap4, 64, 64), std::list<Entity*>{});

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