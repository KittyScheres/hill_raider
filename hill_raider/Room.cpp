#include "Room.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize all of the
	// componets contained inside of the room.
	// --------------------------------------------------
	Room::Room(TileMap* tilemap, std::list<Entity*> enemies, std::list<Entity*> foodPointsPickups)
	{
		m_TileMap = tilemap;
		m_DoorBlockade = new Image("assets/environments/doorway_blockade.png", 0, 0, 4);
		SetDoorBlockadePositionVector();
		m_EnemyList = enemies;
		m_FoodPointsPickupList = foodPointsPickups;
		
		for (Entity* enemy : m_EnemyList) {
			EnemyAnt* enemyAnt = dynamic_cast<EnemyAnt*>(enemy);
			if (enemyAnt != nullptr) {
				enemyAnt->SetRoomCallback(this);
			}
		}
 
		for (Entity* Pickup : m_FoodPointsPickupList) {
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
		int tileHeight = m_TileMap->GetTileHeight();
		int tileWidth = m_TileMap->GetTileWidth();
			
		for (int y = 0; y < TileMap::c_s_TileMapHeight; y++) {
			for (int x = 0; x < TileMap::c_s_TileMapWidth; x++) {
				std::vector<int> doorBlockadePos;
				doorBlockadePos.push_back(0);
				doorBlockadePos.push_back(x * tileWidth);
				doorBlockadePos.push_back(y * tileHeight);

				switch (m_TileMap->GetCollision(tileWidth * x, tileHeight * y))
				{
				case 'w':
				case 't':
					doorBlockadePos[0] = 0;
					m_DoorBlockadePositionList.push_back(doorBlockadePos);
					break;

				case 'd':
				case 'h':
					doorBlockadePos[0] = 1;
					m_DoorBlockadePositionList.push_back(doorBlockadePos);
					break;

				case 's':
				case 'g':
					doorBlockadePos[0] = 3;
					m_DoorBlockadePositionList.push_back(doorBlockadePos);
					break;

				case 'a':
				case 'f':
					doorBlockadePos[0] = 2;
					m_DoorBlockadePositionList.push_back(doorBlockadePos);
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
		for (Entity* enemy : m_EnemyList) {
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
		player->LateUpdate(m_TileMap, GetPLayerCollisionCheckList());
		for (Entity* enemy : m_EnemyList) {
			std::list<Entity*> entityCheckList = std::list<Entity*>(m_EnemyList);
			entityCheckList.remove(enemy);
			entityCheckList.push_back(player);
			enemy->LateUpdate(m_TileMap, entityCheckList);
		}
	}

	// --------------------------------------------------
	// This method is used to draw all of the componets
	// of a room on to the screen.
	// --------------------------------------------------
	void Room::Render(Tmpl8::Surface* screen)
	{
		m_TileMap->Render(screen);

		if (!RoomCleared()) {
			for (std::vector<int> position : m_DoorBlockadePositionList) {
				m_DoorBlockade->SetCurrentXFrame(position[0]);
				m_DoorBlockade->SetPosition(position[1], position[2]);
				m_DoorBlockade->DrawImage(screen);
			}
		}

		for (Entity* foodPointPickup : m_FoodPointsPickupList) {
			foodPointPickup->Render(screen);
		}
		
		for (Entity* enemy : m_EnemyList) {
			enemy->Render(screen);
		}
	}
	
	// --------------------------------------------------
	// This method is used to get the tile map for a room.
	// --------------------------------------------------
	TileMap* Room::GetTileMap()
	{
		return m_TileMap;
	}

	// --------------------------------------------------
	// This method is used to get the memory location of
	// the enemy list of a room.
	// --------------------------------------------------
	std::list<Entity*>* Room::GetEnemyListReference()
	{
		return &m_EnemyList;
	}

	// --------------------------------------------------
	// This method is used to safely remove an entity from
	// the room.
	// --------------------------------------------------
	void Room::RemoveEntity(Entity* entity) {
		if (std::find(m_EnemyList.begin(), m_EnemyList.end(), entity) != m_EnemyList.end()) {
			m_EnemyList.remove(entity);
			SpawnFoodPointsPickupEntity(entity->GetPosition());
			if (entity != nullptr) {
				delete entity;
				entity = nullptr;
			}
		}

		if (std::find(m_FoodPointsPickupList.begin(), m_FoodPointsPickupList.end(), entity) != m_FoodPointsPickupList.end()) {
			m_FoodPointsPickupList.remove(entity);
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
		return m_EnemyList.empty();
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// of the propperties inside of a room.
	// --------------------------------------------------
	Room::~Room()
	{
		if (m_TileMap != nullptr) {
			delete m_TileMap;
			m_TileMap = nullptr;
		}

		if (m_DoorBlockade != nullptr) {
			delete m_DoorBlockade;
			m_DoorBlockade = nullptr;
		}

		if (!m_EnemyList.empty()) {
			for (Entity* enemy : m_EnemyList) {
				if (enemy != nullptr) {
					delete enemy;
					enemy = nullptr;
				}
			}
			m_EnemyList.clear();
		}

		if (!m_FoodPointsPickupList.empty()) {
			for (Entity* foodPointPickup : m_FoodPointsPickupList) {
				if (foodPointPickup != nullptr) {
					delete foodPointPickup;
					foodPointPickup = nullptr;
				}
			}
			m_FoodPointsPickupList.clear();
		}
	}

	// --------------------------------------------------
	// This method is used to get a list of all of the 
	// entity which the player can collide with.
	// --------------------------------------------------
	std::list<Entity*> Room::GetPLayerCollisionCheckList()
	{
		std::list<Entity*> checklist = m_EnemyList;
		for (std::list<Entity*>::const_iterator i = m_FoodPointsPickupList.begin(); i != m_FoodPointsPickupList.end(); i++) {
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
			m_FoodPointsPickupList.push_back(foodPointsPickupEntity);
		}
	}
}