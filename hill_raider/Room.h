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
	// --------------------------------------------------
	// The room class used to creat a room for the floormap
	// of the game. This class contains methods and properties
	// which are used to interact with and keep track of 
	// everything inside of a room.
	// --------------------------------------------------
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
		void LateUpdate(Player* player);
		void Render(Tmpl8::Surface* screen);
		TileMap* GetTileMap();
		std::list<Entity*>* GetEnemyListReference();
		void RemoveEntity(Entity* entity);
		bool RoomCleared();
		~Room();

	private:
		std::list<Entity*> GetPLayerCollisionCheckList();
		void SpawnFoodPointsPickupEntity(std::vector<int> posistion);
	};
}