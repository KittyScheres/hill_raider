#pragma once

#include "RoomCallback.h"
#include "Player.h"
#include "TileMap.h"
#include "EnemyAnt.h"
#include "FoodPointsPickup.h"
#include <list>
#include <typeinfo>

namespace HillRaider
{
	class Room : public RoomCallback
	{
	private:
		TileMap* tileMap = nullptr;
		Image* doorBlockade = nullptr;
		std::vector<std::vector<int>> doorBlockadePositionList = std::vector<std::vector<int>>{};
		std::list<Entity*> enemyList = std::list<Entity*>{};
		std::list<Entity*> foodPointsPickupList = std::list<Entity*>{};

	public:
		Room(TileMap* iTilemap, std::list<Entity*> enemies, std::list<Entity*> foodPointsPickups);
		void SetDoorBlockadePositionVector();
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		void RoomCheckEntityCollision(Player* player);
		void RoomCheckTileMapCollsion();
		TileMap* GetTileMap();
		std::list<Entity*>* GetEnemyListReference();
		void RemoveEntity(Entity* entity);
		bool RoomCleared();
		~Room();

	private:
		void CheckTileMapCollision(Entity* entity);
		void ApplyVerticalTileMapCollision(Entity* entity, int hitboxPointIndex, int hitboxPointYPos);
		void ApplyHorizontalTileMapCollision(Entity* entity, int hitboxPointIndex, int hitboxPointXPos);
		std::list<Entity*> GetPLayerCollisionCheckList();
	};
}