#include "HallwayHorizontal0101.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxccxca edxdaxdaxebxca edxdaxdaxebxca ccxadx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"beaca ca ca ca ca ca ca ca ca ca ca ca ca afd",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxccxca edxdaxdaxebxca edxdaxdaxebxca ccxadx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
	};

	// --------------------------------------------------
	// This method is used to get a randomly selected enemy
	// list for the room.
	// --------------------------------------------------
	static std::list<Entity*> GetEnemyList() {
		switch (std::rand() & 3) {
		case 0:
			return std::list<Entity*>{ new EnemyAnt((64 * 13) + 32, (64 * 1) + 32), new EnemyAnt((64 * 2) + 32, (64 * 7) + 32) };

		case 1:
			return std::list<Entity*>{ new EnemyAnt((64 * 13) + 32, (64 * 1) + 32), new EnemyAnt((64 * 13) + 32, (64 * 7) + 32) };

		case 2:
			return std::list<Entity*>{ new EnemyAnt((64 * 2) + 32, (64 * 1) + 32), new EnemyAnt((64 * 2) + 32, (64 * 7) + 32) };

		default:
			return std::list<Entity*>{ new EnemyAnt((64 * 2) + 32, (64 * 1) + 32), new EnemyAnt((64 * 13) + 32, (64 * 7) + 32) };
		}
	}

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
	HallwayHorizontal0101::HallwayHorizontal0101() : Room(new TileMap("assets/environments/tile_map.png", tilemap, 64, 64), GetEnemyList(), GetPointsPickupList()) {}
}