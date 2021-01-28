#include "DeadEnd0100.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxca ccxca ccxca ca ca ca ca ccxca ccxca adx",
		"bcxca ca ca ca ca ccxca ccxca ca ca ca ca adx",
		"bcxca ca ccxca ca ca ca ca ca ca ccxca ca afd",
		"bcxca ca ca ca ca ccxca ccxca ca ca ca ca adx",
		"bcxca ccxca ccxca ca ca ca ca ccxca ccxca adx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
	};

	static std::list<Entity*> GetEnemyList() {
		switch (std::rand() & 1) {
		case 0:
			return std::list<Entity*>{ new EnemyAnt((64 *7) + 32, (64 * 2) + 32), new EnemyAnt((64 * 7) + 32, (64 * 6) + 32) };

		default:
			return std::list<Entity*>{ new EnemyAnt((64 * 1) + 32, (64 * 2) + 32), new EnemyAnt((64 * 1) + 32, (64 * 6) + 32) };
		}
	}

	static std::list<Entity*> GetPointsPickupList() {
		return std::list<Entity*>();
	}

	DeadEnd0100::DeadEnd0100() : Room(new TileMap("assets/environments/tile_map.png", tilemap, 64, 64), GetEnemyList(), GetPointsPickupList()) {}

	DeadEnd0100::~DeadEnd0100() {}
}