#pragma once

#include "surface.h"
#include "Hitbox.h"
#include <vector>

namespace DownBelow
{
	class Entity
	{
	public:
		enum class MovementDirection { UP = 0, RIGHT, DOWN, LEFT };
	protected:
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
		MovementDirection direction = MovementDirection::UP;
		Hitbox* hitbox = nullptr;
		int distanceMoved = 0;
	protected:
		Entity(int iX, int iY, int iWidth, int iHeight);
		~Entity();
		bool TestBoxCollision(Entity* otherEntity);
		void ApplyEntityCollision(Entity* otherEntity);
	public:
		void Update(float deltaTime);
		void LateUpdate();
		void Render(Tmpl8::Surface* screen);
		std::vector<int> GetPosition();
		int GetWidth();
		int GetHeight();
		MovementDirection GetDirection();
		Hitbox* GetHitbox();
	};
}