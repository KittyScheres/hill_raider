#pragma once

#include "surface.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to create tile maps for the game.
	// This class has been inspired by the tilemap used
	// in the c++ fast track for games programming course.
	// --------------------------------------------------
	class TileMap
	{
	public:
		const static int c_s_TileMapHeight = 9;
		const static int c_s_TileMapWidth = 15 * 3;

	private:
		Tmpl8::Surface* m_TileMapSurface = nullptr;
		char m_TileMap[c_s_TileMapHeight][c_s_TileMapWidth];
		int m_TileHeight = 0;
		int m_TileWidth = 0;
	
	public:
		TileMap(char* tileMapSurfacePath, char tileMap[c_s_TileMapHeight][c_s_TileMapWidth + 1], int tileWidth, int tileHeight);
		void Render(Tmpl8::Surface* screen);
		char GetCollision(int x, int y);
		int GetTileHeight();
		int GetTileWidth();
		~TileMap();

	private:
		void DrawTile(Tmpl8::Surface* screen, int xScreen, int yScreen, int xSurface, int ySurface);
	};
}