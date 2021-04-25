#include "deadEnd0100.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ccxca ccxca ca ca ca ca ccxca ccxca adx",
		"bcxca ca ca ca ca ccxca ccxca ca ca ca ca adx",
		"fcfca ca ccxca ca ca ca ca ca ca ccxca ca afd",
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
			return std::list<Entity*>{ new EnemyAnt((64 *7) + 32, (64 * 2) + 32), new EnemyAnt((64 * 7) + 32, (64 * 6) + 32) };

		default:
			return std::list<Entity*>{ new EnemyAnt((64 * 1) + 32, (64 * 2) + 32), new EnemyAnt((64 * 1) + 32, (64 * 6) + 32) };
		}
	}

	// --------------------------------------------------
	// This method is used to get a randomly selected 
	// food points pickup list for the room.
	// --------------------------------------------------
	static std::list<Entity*> GetPointsPickupList() {
		switch (std::rand() & 1) {
		case 0:
			switch (std::rand() & 3)
			{
			case 0:
				return std::list<Entity*>{ new FoodPointsPickup(20, (64 * 12) + 32, 64 + 32), new FoodPointsPickup(20, (64 * 3) + 32, (64 * 5) + 32) };

			case 1:
				return std::list<Entity*>{ new FoodPointsPickup(20, (64 * 8) + 32, (64 * 6) + 32), new FoodPointsPickup(20, (64 * 11) + 32, (64 * 3) + 32) };

			case 2:
				return std::list<Entity*>{ new FoodPointsPickup(20, 64 + 32, 64 + 32), new FoodPointsPickup(20, (64 * 11) + 32, (64 * 5) + 32) };

			default:
				return std::list<Entity*>{ new FoodPointsPickup(20, (64 * 13) + 32, (64 * 5) + 32), new FoodPointsPickup(20, (64 * 5) + 32, (64 * 4) + 32) };
			}
			break;

		default:
			return std::list<Entity*>{};
		}
	}

	// --------------------------------------------------
	// This constructor is used to setup the premade room.
	// --------------------------------------------------
	DeadEnd0100::DeadEnd0100() : Room(new TileMap("assets/environments/tile_map.png", tilemap, 64, 64), GetEnemyList(), GetPointsPickupList()) {}
}