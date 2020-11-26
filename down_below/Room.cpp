#include "Room.h"

namespace DownBelow
{
	Room::Room(TileMap* iTilemap)
	{
		tileMap = iTilemap;
	}

	void Room::Render(Tmpl8::Surface* screen)
	{
		tileMap->Render(screen);
	}
	
	TileMap* Room::GetTileMap()
	{
		return tileMap;
	}
	
	Room::~Room()
	{
		delete tileMap;
		tileMap = nullptr;
	}
}