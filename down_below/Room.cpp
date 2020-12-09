#include "Room.h"

namespace DownBelow
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Room::Room(TileMap* iTilemap)
	{
		tileMap = iTilemap;
		entity = new RagDoll(64 * 4, 64 * 3, 0.f, 64, 64);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::Update(float deltaTime)
	{
		entity->Update(deltaTime);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::Render(Tmpl8::Surface* screen)
	{
		tileMap->Render(screen);
		entity->Render(screen);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::LateUpdate(Player* player)
	{
		entity->LateUpdate(std::vector<Entity*>{player});
		player->LateUpdate(std::vector<Entity*>{entity});
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	TileMap* Room::GetTileMap()
	{
		return tileMap;
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Room::~Room()
	{
		delete tileMap;
		tileMap = nullptr;

		delete entity;
		entity = nullptr;
	}
}