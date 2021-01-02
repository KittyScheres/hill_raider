#include "HallwayVertical1010.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxaewacxacxacxacxacxacxabx",
		"bcxca ca ca ccxca ca ca ca ca eexca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca dcxca ca ca adx",
		"bcxca ca ca eexca ca ca ca ca dcxca ca ca adx",
		"bcxca ca ca dcxca ca ca ca ca dcxca ca ca adx",
		"bcxca ca ca dcxca ca ca ca ca ecxca ca ca adx",
		"bcxca ca ca dcxca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ecxca ca ca ca ca ccxca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbfsbdxbdxbdxbdxbdxbdxbbx"
	};

	static std::list<Entity*> GetEntityList() {
		switch (std::rand() & 3) {
		case 0:
			return std::list<Entity*>{ new EnemyAnt((64 * 12) + 32, (64 * 1) + 32), new EnemyAnt((64 * 2) + 32, (64 * 7) + 32) };

		case 1:
			return std::list<Entity*>{ new EnemyAnt((64 * 12) + 32, (64 * 7) + 32), new EnemyAnt((64 * 2) + 32, (64 * 7) + 32) };

		case 2:
			return std::list<Entity*>{ new EnemyAnt((64 * 12) + 32, (64 * 1) + 32), new EnemyAnt((64 * 2) + 32, (64 * 1) + 32) };

		case 3:
			return std::list<Entity*>{ new EnemyAnt((64 * 12) + 32, (64 * 7) + 32), new EnemyAnt((64 * 2) + 32, (64 * 1) + 32) };
		}
	}

	HallwayVertical1010::HallwayVertical1010() : Room(new TileMap("assets/tile_maps/tile_map.png", tilemap, 64, 64), GetEntityList()) {}

	HallwayVertical1010::~HallwayVertical1010() {}
}