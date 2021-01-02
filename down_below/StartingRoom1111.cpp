#include "StartingRoom1111.h"

namespace HillRaider
{
	static char tilemap[9][46]{
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

	StartingRoom1111::StartingRoom1111() : Room(new TileMap("assets/tile_maps/tile_map.png", tilemap, 64, 64), std::list<Entity*>{}) {}

	StartingRoom1111::~StartingRoom1111() {}
}