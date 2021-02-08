#include "Corner1100.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxaewacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca eexca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca dcxca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca dcxca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca dcxca ca ca ca ca afd",
		"bcxccxca edxdaxdaxebxca ecxca edxebxca ccxadx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
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
			return std::list<Entity*>{ new EnemyAnt(64 + 32, 64 + 32), new EnemyAnt((64 * 13) + 32, (64 * 7) + 32) };

		default:
			return std::list<Entity*>{ new EnemyAnt(64 + 32, (64 * 7) + 32), new EnemyAnt((64 * 9) + 32, 64 + 32) };
		}
	}

	// --------------------------------------------------
	// This method is used to get a randomly selected 
	// food points pickup list for the room.
	// --------------------------------------------------
	static std::list<Entity*> GetPointsPickupList() {
		switch (std::rand() & 3)
		{
		case 0:
			return std::list<Entity*>{ new FoodPointsPickup(20, (64 * 3) + 32, (64 * 2) + 32), new FoodPointsPickup(20, (64 * 10) + 32, (64 * 6) + 32), new FoodPointsPickup(20, (64 * 12) + 32, (64 * 2) + 32) };

		case 1:
		case 2:
			return std::list<Entity*>{ new FoodPointsPickup(20, (64 * 2) + 32, (64 * 2) + 32), new FoodPointsPickup(20, (64 * 6) + 32, (64 * 3) + 32) };

		default:
			return std::list<Entity*>{ new FoodPointsPickup(20, (64 * 11) + 32, (64 * 2) + 32) };
		}
	}

	// --------------------------------------------------
	// This constructor is used to setup the premade room.
	// --------------------------------------------------
	Corner1100::Corner1100() : Room(new TileMap("assets/environments/tile_map.png", tilemap, 64, 64), GetEnemyList(), GetPointsPickupList()) {}
}