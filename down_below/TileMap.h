#pragma once

#include "surface.h"

namespace DownBelow
{
	class TileMap
	{
	private:
		const static int TILE_MAP_HEIGHT = 9;
		const static int TILE_MAP_WIDHT = 15 * 3;
		Tmpl8::Surface* tileMapSurface = nullptr;
		char tileMap[TILE_MAP_HEIGHT][TILE_MAP_WIDHT];
		int tileHeight = 0;
		int tileWidth = 0;
	
	public:
		TileMap(char* TileMapSurfacePath, char iTileMap[TILE_MAP_HEIGHT][TILE_MAP_WIDHT + 1], int iTileWidth, int iTileHeight);
		void Render(Tmpl8::Surface* screen);
		char GetCollision(int x, int y);
		~TileMap();

	private:
		void DrawTile(Tmpl8::Surface* screen, int xScreen, int yScreen, int xSurface, int ySurface);

	};
}