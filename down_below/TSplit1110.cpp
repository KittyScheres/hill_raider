#include "TSplit1110.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxaewacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca eaxddxca ca ca ca ca ca ca eaxddxca adx",
		"bcxca dbxdexca ca ca ca ca ca ca dbxdexca adx",
		"bcxca ca ca ca ca edxdaxebxca ca ca ca ca afd",
		"bcxca eaxddxca ca ca ca ca ca ca eaxddxca adx",
		"bcxca dbxdexca ca ca ca ca ca ca dbxdexca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbfsbdxbdxbdxbdxbdxbdxbbx"
	};

	static std::list<Entity*> GetEntityList() {
		switch (std::rand() & 3) {
		case 0:
			return std::list<Entity*>{ new EnemyAnt((64 * 1) + 32, (64 * 1) + 32), new EnemyAnt((64 * 3) + 32, (64 * 4) + 32), new EnemyAnt((64 * 1) + 32, (64 * 7) + 32)};

		case 1:
			return std::list<Entity*>{ new EnemyAnt((64 * 13) + 32, (64 * 1) + 32), new EnemyAnt((64 * 3) + 32, (64 * 4) + 32), new EnemyAnt((64 * 13) + 32, (64 * 7) + 32)};

		case 2:
			return std::list<Entity*>{ new EnemyAnt((64 * 7) + 32, (64 * 3) + 32), new EnemyAnt((64 * 7) + 32, (64 * 5) + 32)};

		case 3:
			return std::list<Entity*>{ new EnemyAnt((64 * 5) + 32, (64 * 4) + 32), new EnemyAnt((64 * 9) + 32, (64 * 4) + 32)};
		}
	}

	TSplit1110::TSplit1110() : Room(new TileMap("assets/tile_maps/tile_map.png", tilemap, 64, 64), GetEntityList()) {}
	
	TSplit1110::~TSplit1110() {}
}