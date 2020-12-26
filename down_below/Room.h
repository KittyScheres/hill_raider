#pragma once

#include "RoomCallback.h"
#include "Player.h"
#include "TileMap.h"
#include "RagDoll.h"
#include <list>
#include <typeinfo>

namespace HillRaider
{
	class Room : public RoomCallback
	{
	private:
		TileMap* tileMap = nullptr;
		std::list<Entity*> enemyList = std::list<Entity*>{};

	public:
		Room(TileMap* iTilemap, std::list<Entity*> enemies);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		void RoomCheckEntityCollision(Player* player);
		void RoomCheckTileMapCollsion();
		TileMap* GetTileMap();
		void RemoveEntity(Entity* entity);
		bool RoomCleared();
		~Room();

	private:
		void CheckTileMapCollision(Entity* entity);
		void ApplyVerticalTileMapCollision(Entity* entity, int hitboxPointIndex, int hitboxPointYPos);
		void ApplyHorizontalTileMapCollision(Entity* entity, int hitboxPointIndex, int hitboxPointXPos);
	};
}