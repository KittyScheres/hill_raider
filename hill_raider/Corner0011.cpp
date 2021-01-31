#include "Corner0011.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxccxca edxebxca eexca edxdaxdaxebxca ccxadx",
		"beaca ca ca ca ca dcxca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca dcxca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca dcxca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ecxca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbfsbdxbdxbdxbdxbdxbdxbbx"
	};

	// --------------------------------------------------
	// This method is used to get a randomly selected enemy
	// list for the room.
	// --------------------------------------------------
	static std::list<Entity*> GetEnemyList() {
		switch (std::rand() & 1) {
		case 0:
			return std::list<Entity*>{ new EnemyAnt((64 * 1) + 32, (64 * 1) + 32), new EnemyAnt((64 * 13) + 32, (64 * 7) + 32) };

		default:
			return std::list<Entity*>{ new EnemyAnt((64 * 5) + 32, (64 * 7) + 32), new EnemyAnt((64 * 13) + 32, (64 * 1) + 32) };
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
	Corner0011::Corner0011() : Room(new TileMap("assets/environments/tile_map.png", tilemap, 64, 64), GetEnemyList(), GetPointsPickupList()) {}
}