#include "Floor.h"

namespace DownBelow
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Floor::Floor()
	{
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

		floorMap[1][1] = new Room(new TileMap("assets/gameplay/tile_maps/tile_map.png", tilemap0, 64, 64));

		char tilemap1[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca eexca ca ca ca ca ca adx",
		"bcxca ca ca ca ca edxcbxebxca ca ca ca ca adx",
		"bcxca ca ca ca ca caxecxca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbfsbdxbdxbdxbdxbdxbdxbbx"
		};

		floorMap[1][0] = new Room(new TileMap("assets/gameplay/tile_maps/tile_map.png", tilemap1, 64, 64));

		char tilemap2[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca eexca ca ca ca ca ca adx",
		"bcxca ca ca ca ca edxcbxebxca ca ca ca ca afd",
		"bcxca ca ca ca ca ca ecxca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
		};

		floorMap[0][1] = new Room(new TileMap("assets/gameplay/tile_maps/tile_map.png", tilemap2, 64, 64));

		char tilemap3[9][46]{
		"aaxacxacxacxacxacxacxaewacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca eexca ca ca ca ca ca adx",
		"bcxca ca ca ca ca edxcbxebxca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ecxca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
		};

		floorMap[1][2] = new Room(new TileMap("assets/gameplay/tile_maps/tile_map.png", tilemap3, 64, 64));

		char tilemap4[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca eexca ca ca ca ca ca adx",
		"beaca ca ca ca ca edxcbxebxca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ecxca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
		};

		floorMap[2][1] = new Room(new TileMap("assets/gameplay/tile_maps/tile_map.png", tilemap4, 64, 64));

		currentRoom[0] = 1;
		currentRoom[1] = 1;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Floor::Render(Tmpl8::Surface* screen)
	{
		floorMap[currentRoom[0]][currentRoom[1]]->Render(screen);
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
		case UP:
			--currentRoom[1];
			break;

		case RIGHT:
			++currentRoom[0];
			break;

		case DOWN:
			++currentRoom[1];
			break;

		case LEFT:
			--currentRoom[0];
			break;
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Floor::~Floor()
	{
		delete floorMap[1][1];
		delete floorMap[1][0];
		delete floorMap[1][2];
		delete floorMap[0][1];
		delete floorMap[2][1];
	}
}