#include "TSplit1101.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxaewacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca eaxddxca ca ca ca ca ca ca eaxddxca adx",
		"bcxca dbxdexca ca ca ca ca ca ca dbxdexca adx",
		"beaca ca ca ca ca edxdaxebxca ca ca ca ca afd",
		"bcxca eaxddxca ca ca ca ca ca ca eaxddxca adx",
		"bcxca dbxdexca ca ca ca ca ca ca dbxdexca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
	};

	static std::list<Entity*> GetEntityList() {
		switch (std::rand() & 3) {
		case 0:
			return std::list<Entity*>{ new EnemyAnt((64 * 3) + 32, (64 * 7) + 32), new EnemyAnt((64 * 7) + 32, (64 * 6) + 32), new EnemyAnt((64 * 11) + 32, (64 * 7) + 32) };

		case 1:
			return std::list<Entity*>{ new EnemyAnt((64 * 1) + 32, (64 * 1) + 32), new EnemyAnt((64 * 7) + 32, (64 * 6) + 32), new EnemyAnt((64 * 13) + 32, (64 * 13) + 32) };

		case 2:
			return std::list<Entity*>{ new EnemyAnt((64 * 3) + 32, (64 * 4) + 32), new EnemyAnt((64 * 11) + 32, (64 * 4) + 32) };

		case 3:
			return std::list<Entity*>{ new EnemyAnt((64 * 1) + 32, (64 * 7) + 32), new EnemyAnt((64 * 13) + 32, (64 * 1) + 32) };
		}
	}

	TSplit1101::TSplit1101() : Room(new TileMap("assets/tile_maps/tile_map.png", tilemap, 64, 64), GetEntityList()) {}

	TSplit1101::~TSplit1101() {}
}