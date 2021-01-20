#include "TileMap.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize and setup
	// the tile map object.
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
	// This method is used to draw a tile on to the screen.
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
	// This mehtod is used to draw all of the tiles of
	// the tilemap on to the screen.
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
	// This method is used to get the collision char for
	// a spesific tile on the tile map.
	// --------------------------------------------------
	char TileMap::GetCollision(int x, int y)
	{
		x = x / tileWidth;
		y = y / tileHeight;
		return tileMap[y][(x * 3) + 2];
	}

	// --------------------------------------------------
	// This mehtod is used to get the height of a tile
	// on the tile map.
	// --------------------------------------------------
	int TileMap::GetTileHeight()
	{
		return tileHeight;
	}

	// --------------------------------------------------
	// This mehtod is used to get the width of a tile
	// on the tile map.
	// --------------------------------------------------
	int TileMap::GetTileWidth()
	{
		return tileWidth;
	}
	
	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// for the source of the tile map.
	// --------------------------------------------------
	TileMap::~TileMap()
	{
		if (tileMapSurface != nullptr) {
			delete tileMapSurface;
			tileMapSurface = nullptr;
		}
	}
}