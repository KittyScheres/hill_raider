#include "Room.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Room::Room(TileMap* iTilemap, std::list<Entity*> enemies)
	{
		tileMap = iTilemap;
		enemyList = enemies;
		
		for (Entity* enemy : enemyList) {
			RagDoll* ragdoll = dynamic_cast<RagDoll*>(enemy);
			if (ragdoll != nullptr) {
				ragdoll->SetRoomCallback(this);
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
		for (Entity* enemy : enemyList) {
			enemy->Render(screen);
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::RoomCheckEntityCollision(Player* player)
	{
		for (Entity* enemy : enemyList) {
			std::list<Entity*> entityCheckList = std::list<Entity*>(enemyList);
			entityCheckList.remove(enemy);
			entityCheckList.push_back(player);
			enemy->LateUpdate(entityCheckList);
		}
		player->LateUpdate(enemyList);
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
	void Room::RemoveEntity(Entity* entity) {
		if (std::find(enemyList.begin(), enemyList.end(), entity) != enemyList.end()) {
			enemyList.remove(entity);
			delete entity;
			entity = nullptr;
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

		if (!enemyList.empty()) {
			for (Entity* enemy : enemyList) {
				delete enemy;
				enemy = nullptr;
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