#include "TileMap.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize and setup
	// the tile map object.
	// --------------------------------------------------
	TileMap::TileMap(char* tileMapSurfacePath, char tileMap[c_s_TileMapHeight][c_s_TileMapWidth + 1], int tileWidth, int tileHeight)
	{
		m_TileMapSurface = new Tmpl8::Surface(tileMapSurfacePath);
		for (int i = 0; i < c_s_TileMapHeight; i++) {
			for (int k = 0; k < c_s_TileMapWidth; k++) {
				m_TileMap[i][k] = tileMap[i][k];
			}
		}
		m_TileHeight = tileHeight;
		m_TileWidth = tileWidth;
	}

	// --------------------------------------------------
	// This method is used to draw a tile on to the screen.
	// --------------------------------------------------
	void TileMap::DrawTile(Tmpl8::Surface* screen, int xScreen, int yScreen, int xSurface, int ySurface)
	{
		for (int y = 0; y < m_TileHeight; y++) {
			if ((((y + yScreen) <= screen->GetHeight()) && ((y + yScreen) >= 0)) && (((y + ySurface) <= m_TileMapSurface->GetHeight()) && ((y + ySurface) >= 0))) {
				for (int x = 0; x < m_TileWidth; x++) {
					if ((((x + xScreen) <= screen->GetWidth()) && ((x + xScreen) >= 0)) && (((x + xSurface) <= m_TileMapSurface->GetWidth()) && ((x + xSurface) >= 0))) {
						screen->GetBuffer()[(x + xScreen) + ((y + yScreen) * screen->GetWidth())] = m_TileMapSurface->GetBuffer()[(x + xSurface) + ((y + ySurface) * m_TileMapSurface->GetWidth())];
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
		for (int y = 0; y < c_s_TileMapHeight; y++) {
			for (int x = 0; x < (c_s_TileMapWidth / 3); x++) {
				DrawTile(screen, x * m_TileWidth, y * m_TileHeight, (m_TileMap[y][(x * 3) + 1] - 'a') * m_TileHeight, (m_TileMap[y][(x * 3)] - 'a') * m_TileWidth);
			}
		}
	}
	
	// --------------------------------------------------
	// This method is used to get the collision char for
	// a spesific tile on the tile map.
	// --------------------------------------------------
	char TileMap::GetCollision(int x, int y)
	{
		char collisionChar = ' ';
		x = x / m_TileWidth;
		y = y / m_TileHeight;
		
		if (x < (c_s_TileMapWidth / 3) && y < c_s_TileMapHeight) {
			collisionChar = m_TileMap[y][(x * 3) + 2];
		}

		return collisionChar;
	}

	// --------------------------------------------------
	// This mehtod is used to get the height of a tile
	// on the tile map.
	// --------------------------------------------------
	int TileMap::GetTileHeight()
	{
		return m_TileHeight;
	}

	// --------------------------------------------------
	// This mehtod is used to get the width of a tile
	// on the tile map.
	// --------------------------------------------------
	int TileMap::GetTileWidth()
	{
		return m_TileWidth;
	}
	
	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// for the source of the tile map.
	// --------------------------------------------------
	TileMap::~TileMap()
	{
		if (m_TileMapSurface != nullptr) {
			delete m_TileMapSurface;
			m_TileMapSurface = nullptr;
		}
	}
}