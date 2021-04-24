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
		int m_X = 0;
		int m_Y = 0;
		int m_Width = 0;
		int m_Height = 0;
		Direction m_Direction = Direction::UP;
		Hitbox* m_Hitbox = nullptr;
		int m_DistanceMoved = 0;

	public:
		virtual void Update(float deltaTime) {}
		virtual void LateUpdate(TileMap* tileMap, std::list<Entity*> entityList) {}
		virtual void Render(Tmpl8::Surface* screen) {}
		virtual void TakeDamage() {}
		virtual void SetPosition(int x, int y);
		std::vector<int> GetPosition();
		int GetWidth();
		int GetHeight();
		Direction GetDirection();
		Hitbox* GetHitbox();
		virtual ~Entity();

	protected:
		Entity(int x, int y, int width, int height);
		bool TestBoxCollision(Hitbox* myHitbox, Entity* otherEntity);
		void ApplyEntityCollision(Entity* otherEntity);
		void CheckTileMapCollision(short& _hitboxPoint, char& _collisionChar, TileMap* tileMap);
		void ApplyVerticalTileMapCollision(int hitboxPointIndex, int hitboxPointYPos);
		void ApplyHorizontalTileMapCollision(int hitboxPointIndex, int hitboxPointXPos);
	};
}