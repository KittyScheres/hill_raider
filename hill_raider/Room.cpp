#include "Room.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Room::Room(TileMap* iTilemap, std::list<Entity*> enemies)
	{
		tileMap = iTilemap;
		doorBlockade = new Image("assets/environments/doorway_blockade.png", 0, 0, 4);
		SetDoorBlockadePositionVector();
		enemyList = enemies;
		
		for (Entity* enemy : enemyList) {
			EnemyAnt* enemyAnt = dynamic_cast<EnemyAnt*>(enemy);
			if (enemyAnt != nullptr) {
				enemyAnt->SetRoomCallback(this);
			}
		}

	}

	// --------------------------------------------------
	//
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
					doorBlockadePos[0] = 0;
					doorBlockadePositionList.push_back(doorBlockadePos);
					break;

				case 'd':
					doorBlockadePos[0] = 1;
					doorBlockadePositionList.push_back(doorBlockadePos);
					break;

				case 's':
					doorBlockadePos[0] = 3;
					doorBlockadePositionList.push_back(doorBlockadePos);
					break;

				case 'a':
					doorBlockadePos[0] = 2;
					doorBlockadePositionList.push_back(doorBlockadePos);
					break;
				}
			}
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::Update(float deltaTime)
	{
		for (Entity* enemy : enemyList) {
			enemy->Update(deltaTime);
		}
	}

	// --------------------------------------------------
	//
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
		
		for (Entity* enemy : enemyList) {
			enemy->Render(screen);
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::RoomCheckEntityCollision(Player* player)
	{
		player->LateUpdate(enemyList);
		for (Entity* enemy : enemyList) {
			std::list<Entity*> entityCheckList = std::list<Entity*>(enemyList);
			entityCheckList.remove(enemy);
			entityCheckList.push_back(player);
			enemy->LateUpdate(entityCheckList);
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::RoomCheckTileMapCollsion()
	{
		for (Entity* enemy : enemyList) {
			CheckTileMapCollision(enemy);
		}
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
	std::list<Entity*>* Room::GetEnemyListReference()
	{
		return &enemyList;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::RemoveEntity(Entity* entity) {
		if (std::find(enemyList.begin(), enemyList.end(), entity) != enemyList.end()) {
			enemyList.remove(entity);
			if (entity != nullptr) {
				delete entity;
				entity = nullptr;
			}
		}
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	bool Room::RoomCleared()
	{
		return enemyList.empty();
	}

	// --------------------------------------------------
	//
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
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::CheckTileMapCollision(Entity* entity)
	{
		std::vector<std::vector<int>> hitbox = entity->GetHitbox()->GetBoxPoints();
		char collisionChar = ' ';
		int index = 0;

		for (int i = 0; i < 4; i++) {
			if (tileMap->GetCollision(hitbox[i][0], hitbox[i][1]) != ' ' && collisionChar != 'x') {
				collisionChar = tileMap->GetCollision(hitbox[i][0], hitbox[i][1]);
				index = i;
			}
		}

		if(collisionChar != ' '){
			switch (entity->GetDirection())
			{
			case Entity::MovementDirection::UP:
			case Entity::MovementDirection::DOWN:
				ApplyVerticalTileMapCollision(entity, index, hitbox[index][1]);
				break;

			case Entity::MovementDirection::LEFT:
			case Entity::MovementDirection::RIGHT:
				ApplyHorizontalTileMapCollision(entity, index, hitbox[index][0]);
				break;
			}
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::ApplyVerticalTileMapCollision(Entity* entity, int hitboxPointIndex, int hitboxPointYPos)
	{
		switch (hitboxPointIndex & 2)
		{
		case 0:
			entity->SetPosition(entity->GetPosition()[0], entity->GetPosition()[1] + (64 - ((hitboxPointYPos & 63) - 1)));
			break;

		case 2:
			entity->SetPosition(entity->GetPosition()[0], entity->GetPosition()[1] - ((hitboxPointYPos & 63) + 1));
			break;
		}

	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::ApplyHorizontalTileMapCollision(Entity* entity, int hitboxPointIndex, int hitboxPointXPos)
	{
		switch (hitboxPointIndex & 1)
		{
		case 0:
			entity->SetPosition(entity->GetPosition()[0] + (64 - ((hitboxPointXPos & 63) - 1)), entity->GetPosition()[1]);
			break;

		case 1:
			entity->SetPosition(entity->GetPosition()[0] - ((hitboxPointXPos & 63) + 1), entity->GetPosition()[1]);
			break;
		}
	}
}