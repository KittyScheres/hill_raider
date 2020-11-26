#pragma once

#include "surface.h"
#include "TileMap.h"

namespace DownBelow
{
	class Room
	{
	private:
		TileMap* tileMap = nullptr;

	public:
		Room(TileMap* iTilemap);
		void Render(Tmpl8::Surface* screen);
		TileMap* GetTileMap();
		~Room();
	};
}