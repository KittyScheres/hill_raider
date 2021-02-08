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
		switch (std::rand() & 1) {
		case 0:
			switch (std::rand() & 3)
			{
			case 0:
				return std::list<Entity*>{ new FoodPointsPickup(20, (64 * 11) + 32, (64 * 2) + 32) };

			case 1:
				return std::list<Entity*>{ new FoodPointsPickup(20, 64 + 32, (64 * 7) + 32) };

			case 2:
				return std::list<Entity*>{ new FoodPointsPickup(20, (64 * 4) + 32, (64 * 3) + 32) };

			default:
				return std::list<Entity*>{ new FoodPointsPickup(20, (64 * 10) + 32, (64 * 6) + 32) };
			}
			break;

		default:
			return std::list<Entity*>{};
		}
	}

	// --------------------------------------------------
	// This constructor is used to setup the premade room.
	// --------------------------------------------------
	CrossRoad1111::CrossRoad1111() : Room(new TileMap("assets/environments/tile_map.png", tilemap, 64, 64), std::list<Entity*>{}, GetPointsPickupList()) {}
}