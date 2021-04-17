#include "Room.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize all of the
	// componets contained inside of the room.
	// --------------------------------------------------
	Room::Room(TileMap* iTilemap, std::list<Entity*> enemies, std::list<Entity*> foodPointsPickups)
	{
		tileMap = iTilemap;
		doorBlockade = new Image("assets/environments/doorway_blockade.png", 0, 0, 4);
		SetDoorBlockadePositionVector();
		enemyList = enemies;
		foodPointsPickupList = foodPointsPickups;
		
		for (Entity* enemy : enemyList) {
			EnemyAnt* enemyAnt = dynamic_cast<EnemyAnt*>(enemy);
			if (enemyAnt != nullptr) {
				enemyAnt->SetRoomCallback(this);
			}
		}
 
		for (Entity* Pickup : foodPointsPickupList) {
			FoodPointsPickup* foodPointPickup = dynamic_cast<FoodPointsPickup*>(Pickup);
			if (foodPointPickup != nullptr) {
				foodPointPickup->SetRoomCallback(this);
			}
		}
	}

	// --------------------------------------------------
	// This method is used to get the possitions of all of
	// the doors in a room, these positions will be used to
	// set the position for the blockade image when the 
	// room has not been cleared.
	// --------------------------------------------------
	void Room::SetDoorBlockadePositionVector() {
		int tileHeight = tileMap->GetTileHeight();
		int tileWidth = tileMap->GetTileWidth();
			
		for (int y = 0; y < TileMap::TILE_MAP_HEIGHT; y++) {
			for (int x = 0; x < TileMap::TILE_MAP_WIDHT; x++) {
				std::vector<int> doorBlockadePos;
				doorBlockadePos.push_back(0);
				doorBlockadePos.push_back(x * tileWidth);
				doorBlockadePos.push_back(y * tileHeight);

				switch (tileMap->GetCollision(tileWidth * x, tileHeight * y))
				{
				case 'w':
				case 't':
					doorBlockadePos[0] = 0;
					doorBlockadePositionList.push_back(doorBlockadePos);
					break;

				case 'd':
				case 'h':
					doorBlockadePos[0] = 1;
					doorBlockadePositionList.push_back(doorBlockadePos);
					break;

				case 's':
				case 'g':
					doorBlockadePos[0] = 3;
					doorBlockadePositionList.push_back(doorBlockadePos);
					break;

				case 'a':
				case 'f':
					doorBlockadePos[0] = 2;
					doorBlockadePositionList.push_back(doorBlockadePos);
					break;
				}
			}
		}
	}

	// --------------------------------------------------
	// This method is used to update the enemies inside
	// of a room.
	// --------------------------------------------------
	void Room::Update(float deltaTime)
	{
		for (Entity* enemy : enemyList) {
			enemy->Update(deltaTime);
		}
	}

	// --------------------------------------------------
	// This method is used to call the late update method
	// for all of the entities in a room, this includes
	// the player.
	// --------------------------------------------------
	void Room::LateUpdate(Player* player)
	{
		player->LateUpdate(tileMap, GetPLayerCollisionCheckList());
		for (Entity* enemy : enemyList) {
			std::list<Entity*> entityCheckList = std::list<Entity*>(enemyList);
			entityCheckList.remove(enemy);
			entityCheckList.push_back(player);
			enemy->LateUpdate(tileMap, entityCheckList);
		}
	}

	// --------------------------------------------------
	// This method is used to draw all of the componets
	// of a room on to the screen.
	// --------------------------------------------------
	void Room::Render(Tmpl8::Surface* screen)
	{
		tileMap->Render(screen);

		if (!RoomCleared()) {
			for (std::vector<int> position : doorBlockadePositionList) {
				doorBlockade->SetCurrentXFrame(position[0]);
				doorBlockade->SetPosition(position[1], position[2]);
				doorBlockade->DrawImage(screen);
			}
		}

		for (Entity* foodPointPickup : foodPointsPickupList) {
			foodPointPickup->Render(screen);
		}
		
		for (Entity* enemy : enemyList) {
			enemy->Render(screen);
		}
	}
	
	// --------------------------------------------------
	// This method is used to get the tile map for a room.
	// --------------------------------------------------
	TileMap* Room::GetTileMap()
	{
		return tileMap;
	}

	// --------------------------------------------------
	// This method is used to get the memory location of
	// the enemy list of a room.
	// --------------------------------------------------
	std::list<Entity*>* Room::GetEnemyListReference()
	{
		return &enemyList;
	}

	// --------------------------------------------------
	// This method is used to safely remove an entity from
	// the room.
	// --------------------------------------------------
	void Room::RemoveEntity(Entity* entity) {
		if (std::find(enemyList.begin(), enemyList.end(), entity) != enemyList.end()) {
			enemyList.remove(entity);
			SpawnFoodPointsPickupEntity(entity->GetPosition());
			if (entity != nullptr) {
				delete entity;
				entity = nullptr;
			}
		}

		if (std::find(foodPointsPickupList.begin(), foodPointsPickupList.end(), entity) != foodPointsPickupList.end()) {
			foodPointsPickupList.remove(entity);
			if (entity != nullptr) {
				delete entity;
				entity = nullptr;
			}
		}
	}
	
	// --------------------------------------------------
	// This method is used to check if a room still has
	// enemy ants inside of it.
	// --------------------------------------------------
	bool Room::RoomCleared()
	{
		return enemyList.empty();
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// of the propperties inside of a room.
	// --------------------------------------------------
	Room::~Room()
	{
		if (tileMap != nullptr) {
			delete tileMap;
			tileMap = nullptr;
		}

		if (doorBlockade != nullptr) {
			delete doorBlockade;
			doorBlockade = nullptr;
		}

		if (!enemyList.empty()) {
			for (Entity* enemy : enemyList) {
				if (enemy != nullptr) {
					delete enemy;
					enemy = nullptr;
				}
			}
			enemyList.clear();
		}

		if (!foodPointsPickupList.empty()) {
			for (Entity* foodPointPickup : foodPointsPickupList) {
				if (foodPointPickup != nullptr) {
					delete foodPointPickup;
					foodPointPickup = nullptr;
				}
			}
			foodPointsPickupList.clear();
		}
	}

	// --------------------------------------------------
	// This method is used to get a list of all of the 
	// entity which the player can collide with.
	// --------------------------------------------------
	std::list<Entity*> Room::GetPLayerCollisionCheckList()
	{
		std::list<Entity*> checklist = enemyList;
		for (std::list<Entity*>::const_iterator i = foodPointsPickupList.begin(); i != foodPointsPickupList.end(); i++) {
			checklist.push_back(*i);
		}
		return checklist;
	}

	// --------------------------------------------------
	// This method is used to spawn a food points pickup
	// entity when an enemy ant has been defeated.
	// --------------------------------------------------
	void Room::SpawnFoodPointsPickupEntity(std::vector<int> posistion)
	{
		if ((rand() & 3) == 0) {
			short pointsValue = 0;

			switch (rand() & 7)
			{
			case 0:
			case 1:
				pointsValue = 25;
				break;

			case 2:
			case 3:
				pointsValue = 50;
				break;

			case 4:
			case 5:
				pointsValue = 75;
				break;

			case 6:
			case 7:
				pointsValue = 100;
				break;
			}

			FoodPointsPickup* foodPointsPickupEntity = new FoodPointsPickup(pointsValue, posistion[0], posistion[1]);
			foodPointsPickupEntity->SetRoomCallback(this);
			foodPointsPickupList.push_back(foodPointsPickupEntity);
		}
	}
}