#include "DeadEnd0001.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ccxca ccxca ca ca ca ca ccxca ccxca adx",
		"bcxca ca ca ca ca ccxca ccxca ca ca ca ca adx",
		"beaca ca ccxca ca ca ca ca ca ca ccxca ca fbh",
		"bcxca ca ca ca ca ccxca ccxca ca ca ca ca adx",
		"bcxca ccxca ccxca ca ca ca ca ccxca ccxca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
	};

	// --------------------------------------------------
	// This method is used to get a randomly selected enemy
	// list for the room.
	// --------------------------------------------------
	static std::list<Entity*> GetEnemyList() {
		switch (std::rand() & 1) {
		case 0:
			return std::list<Entity*>{ new EnemyAnt((64 * 7) + 32, (64 * 2) + 32), new EnemyAnt((64 * 7) + 32, (64 * 6) + 32) };

		default:
			return std::list<Entity*>{ new EnemyAnt((64 * 13) + 32, (64 * 2) + 32), new EnemyAnt((64 * 13) + 32, (64 * 6) + 32) };
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
	DeadEnd0001::DeadEnd0001() : Room(new TileMap("assets/environments/tile_map.png", tilemap, 64, 64), GetEnemyList(), GetPointsPickupList()) {}
}