#include "Room.h"

namespace DownBelow
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Room::Room(TileMap* iTilemap)
	{
		tileMap = iTilemap;
		entity = new RagDoll(64 * 4, 64 * 3, 150.f, 64, 64);
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
		CheckTileMapCollision(entity);

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

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Room::CheckTileMapCollision(Entity* entity)
	{
		std::vector<std::vector<int>> hitbox = entity->GetHitbox()->GetBoxPoints();
		char collisionChar = ' ';
		int pointX = 0;
		int pointY = 0;

		for (int i = 0; i < 4; i++) {
			if (tileMap->GetCollision(hitbox[i][0], hitbox[i][1]) != ' ' && collisionChar != 'x') {
				collisionChar = tileMap->GetCollision(hitbox[i][0], hitbox[i][1]);
				pointX = hitbox[i][0];
				pointY = hitbox[i][1];
			}
		}

		if(collisionChar != ' '){
			switch (entity->GetDirection())
			{
			case Entity::MovementDirection::UP:
				entity->SetPosition(entity->GetPosition()[0], entity->GetPosition()[1] + (64 - ((pointY % 64) - 1)));
				break;

			case Entity::MovementDirection::RIGHT:
				entity->SetPosition(entity->GetPosition()[0] - ((pointX % 64) + 1), entity->GetPosition()[1]);
				break;

			case Entity::MovementDirection::DOWN:
				entity->SetPosition(entity->GetPosition()[0], entity->GetPosition()[1] - ((pointY % 64) + 1));
				break;

			case Entity::MovementDirection::LEFT:
				entity->SetPosition(entity->GetPosition()[0] + (64 - ((pointX % 64) - 1)), entity->GetPosition()[1]);
				break;
			}
		}
	}
}