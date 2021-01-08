#include "TileMap.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	TileMap::TileMap(char* TileMapSurfacePath, char iTileMap[TILE_MAP_HEIGHT][TILE_MAP_WIDHT + 1], int iTileWidth, int iTileHeight)
	{
		tileMapSurface = new Tmpl8::Surface(TileMapSurfacePath);
		for (int i = 0; i < TILE_MAP_HEIGHT; i++) {
			for (int k = 0; k < TILE_MAP_WIDHT; k++) {
				tileMap[i][k] = iTileMap[i][k];
			}
		}
		tileHeight = iTileHeight;
		tileWidth = iTileWidth;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void TileMap::DrawTile(Tmpl8::Surface* screen, int xScreen, int yScreen, int xSurface, int ySurface)
	{
		for (int y = 0; y < tileHeight; y++) {
			if ((((y + yScreen) <= screen->GetHeight()) && ((y + yScreen) >= 0)) && (((y + ySurface) <= tileMapSurface->GetHeight()) && ((y + ySurface) >= 0))) {
				for (int x = 0; x < tileWidth; x++) {
					if ((((x + xScreen) <= screen->GetWidth()) && ((x + xScreen) >= 0)) && (((x + xSurface) <= tileMapSurface->GetWidth()) && ((x + xSurface) >= 0))) {
						screen->GetBuffer()[(x + xScreen) + ((y + yScreen) * screen->GetWidth())] = tileMapSurface->GetBuffer()[(x + xSurface) + ((y + ySurface) * tileMapSurface->GetWidth())];
					}
				}
			}
		}
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	void TileMap::Render(Tmpl8::Surface* screen)
	{
		for (int y = 0; y < TILE_MAP_HEIGHT; y++) {
			for (int x = 0; x < (TILE_MAP_WIDHT / 3); x++) {
				DrawTile(screen, x * tileWidth, y * tileHeight, (tileMap[y][(x * 3) + 1] - 'a') * tileHeight, (tileMap[y][(x * 3)] - 'a') * tileWidth);
			}
		}
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	char TileMap::GetCollision(int x, int y)
	{
		x = x / tileWidth;
		y = y / tileHeight;
		return tileMap[y][(x * 3) + 2];
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int TileMap::GetTileHeight()
	{
		return tileHeight;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int TileMap::GetTileWidth()
	{
		return tileWidth;
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	TileMap::~TileMap()
	{
		if (tileMapSurface != nullptr) {
			delete tileMapSurface;
			tileMapSurface = nullptr;
		}
	}
}