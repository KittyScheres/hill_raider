#include "HallwayHorizontal0101.h"

namespace HillRaider
{
	static char tilemap[9][46]{
		"aaxacxacxacxacxacxacxacxacxacxacxacxacxacxabx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxccxca edxdaxdaxdaxdaxdaxdaxdaxdaxdaxebxadx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"beaca ca ca ca ca ca ca ca ca ca ca ca ca afd",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"bcxedxdaxdaxdaxdaxdaxdaxdaxdaxdaxebxca ccxadx",
		"bcxca ca ca ca ca ca ca ca ca ca ca ca ca adx",
		"baxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbdxbbx"
	};

	static std::list<Entity*> GetEntityList() {
		switch (std::rand() & 3) {
		case 0:
			return std::list<Entity*>{ new RagDoll((64 * 13) + 32, (64 * 1) + 32), new RagDoll((64 * 2) + 32, (64 * 7) + 32) };

		case 1:
			return std::list<Entity*>{ new RagDoll((64 * 13) + 32, (64 * 1) + 32), new RagDoll((64 * 13) + 32, (64 * 7) + 32) };

		case 2:
			return std::list<Entity*>{ new RagDoll((64 * 2) + 32, (64 * 1) + 32), new RagDoll((64 * 2) + 32, (64 * 7) + 32) };

		case 3:
			return std::list<Entity*>{ new RagDoll((64 * 2) + 32, (64 * 1) + 32), new RagDoll((64 * 13) + 32, (64 * 7) + 32) };
		}
	}

	HallwayHorizontal0101::HallwayHorizontal0101() : Room(new TileMap("assets/tile_maps/tile_map.png", tilemap, 64, 64), GetEntityList()) {}

	HallwayHorizontal0101::~HallwayHorizontal0101() {}
}