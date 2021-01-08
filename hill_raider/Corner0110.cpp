#include "Corner0110.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxccxca edxdaxdaxebxca eexca edxebxca ccxadx",
		"bcxca ca ca ca ca ca ca dcxca ca ca ca ca afd",
		"bcxca ca ca ca ca ca ca dcxca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca dcxca ca ca ca ca adx",
		"bcxca ca ca ca ca ca ca ecxca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbfsbdxbdxbdxbdxbdxbdxbbx"
	};

	static std::list<Entity*> GetEntityList() {
		switch (std::rand() & 1) {
		case 0:
			return std::list<Entity*>{ new EnemyAnt((64 * 1) + 32, (64 * 1) + 32), new EnemyAnt((64 * 9) + 32, (64 * 7) + 32) };

		case 1:
			return std::list<Entity*>{ new EnemyAnt((64 * 1) + 32, (64 * 7) + 32), new EnemyAnt((64 * 13) + 32, (64 * 1) + 32) };
		}
	}

	Corner0110::Corner0110() : Room(new TileMap("assets/tile_maps/tile_map.png", tilemap, 64, 64), GetEntityList()) {}

	Corner0110::~Corner0110() {}
}