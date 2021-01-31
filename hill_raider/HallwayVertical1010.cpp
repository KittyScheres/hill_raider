#include "HallwayVertical1010.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxaewacxacxacxacxacxacxabx",
		"bcxca ca ca ccxca ca ca ca ca ccxca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca eexca ca ca ca ca eexca ca ca adx",
		"bcxca ca ca dcxca ca ca ca ca dcxca ca ca adx",
		"bcxca ca ca ecxca ca ca ca ca ecxca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ccxca ca ca ca ca ccxca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbfsbdxbdxbdxbdxbdxbdxbbx"
	};

	// --------------------------------------------------
	// This method is used to get a randomly selected enemy
	// list for the room.
	// --------------------------------------------------
	static std::list<Entity*> GetEnemyList() {
		switch (std::rand() & 3) {
		case 0:
			return std::list<Entity*>{ new EnemyAnt((64 * 12) + 32, (64 * 1) + 32), new EnemyAnt((64 * 2) + 32, (64 * 7) + 32) };

		case 1:
			return std::list<Entity*>{ new EnemyAnt((64 * 12) + 32, (64 * 7) + 32), new EnemyAnt((64 * 2) + 32, (64 * 7) + 32) };

		case 2:
			return std::list<Entity*>{ new EnemyAnt((64 * 12) + 32, (64 * 1) + 32), new EnemyAnt((64 * 2) + 32, (64 * 1) + 32) };

		default:
			return std::list<Entity*>{ new EnemyAnt((64 * 12) + 32, (64 * 7) + 32), new EnemyAnt((64 * 2) + 32, (64 * 1) + 32) };
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
	HallwayVertical1010::HallwayVertical1010() : Room(new TileMap("assets/environments/tile_map.png", tilemap, 64, 64), GetEnemyList(), GetPointsPickupList()) {}
}