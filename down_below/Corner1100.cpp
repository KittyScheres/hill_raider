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

	static std::list<Entity*> GetEntityList() {
		switch (std::rand() & 1) {
		case 0:
			return std::list<Entity*>{ new EnemyAnt((64 * 1) + 32, (64 * 1) + 32), new EnemyAnt((64 * 13) + 32, (64 * 7) + 32) };

		case 1:
			return std::list<Entity*>{ new EnemyAnt((64 * 1) + 32, (64 * 7) + 32), new EnemyAnt((64 * 9) + 32, (64 * 1) + 32) };
		}
	}

	Corner1100::Corner1100() : Room(new TileMap("assets/tile_maps/tile_map.png", tilemap, 64, 64), GetEntityList()) {}

	Corner1100::~Corner1100() {}
}