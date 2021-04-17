#pragma once

#include "surface.h"
#include "Hitbox.h"
#include "TileMap.h"
#include "Direction.h"
#include <vector>
#include <list>

namespace HillRaider
{
	// --------------------------------------------------
	// The entity class is a base class for creating entities.
	// The class contains methods and properties which can
	// be used by all entities in the game.
	// --------------------------------------------------
	class Entity
	{
	protected:
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
		Direction direction = Direction::UP;
		Hitbox* hitbox = nullptr;
		int distanceMoved = 0;

	public:
		virtual void Update(float deltaTime) {}
		virtual void LateUpdate(TileMap* tileMap, std::list<Entity*> entityList) {}
		virtual void Render(Tmpl8::Surface* screen) {}
		virtual void TakeDamage() {}
		virtual void SetPosition(int iX, int iY);
		std::vector<int> GetPosition();
		int GetWidth();
		int GetHeight();
		Direction GetDirection();
		Hitbox* GetHitbox();
		virtual ~Entity();

	protected:
		Entity(int iX, int iY, int iWidth, int iHeight);
		bool TestBoxCollision(Hitbox* myHitbox, Entity* otherEntity);
		void ApplyEntityCollision(Entity* otherEntity);
		void CheckTileMapCollision(short& _hitboxPoint, char& _collisionChar, TileMap* tileMap);
		void ApplyVerticalTileMapCollision(int hitboxPointIndex, int hitboxPointYPos);
		void ApplyHorizontalTileMapCollision(int hitboxPointIndex, int hitboxPointXPos);
	};
}