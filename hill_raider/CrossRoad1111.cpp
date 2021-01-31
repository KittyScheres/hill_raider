#include "CrossRoad1111.h"

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

	// --------------------------------------------------
	// This method is used to get a randomly selected 
	// food points pickup list for the room.
	// --------------------------------------------------
	static std::list<Entity*> GetPointsPickupList() {
		return std::list<Entity*>();
	}

	// --------------------------------------------------
	// This constructor is used to setup the premade room.
	// --------------------------------------------------
	CrossRoad1111::CrossRoad1111() : Room(new TileMap("assets/environments/tile_map.png", tilemap, 64, 64), std::list<Entity*>{}, GetPointsPickupList()) {}
}