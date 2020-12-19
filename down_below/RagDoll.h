#pragma once

#include "RoomCallback.h"
#include "Entity.h"
#include "Image.h"
#include "AStar.h"

namespace HillRaider
{
	class RagDoll : public Entity
	{
	private:
		RoomCallback* callback = nullptr;
		Image* ragDollSprite = nullptr;
		float speed = 0.f;
		int ragdollHealt = 2;
	public:
		RagDoll(RoomCallback* iCallback, int iX, int iY, float iSpeed, int iWidth, int iHeight);
		void Update(float deltaTime);
		void LateUpdate(std::vector<Entity*> entityList);
		void Render(Tmpl8::Surface* screen);
		void TakeDamage();
		MovementDirection GetDirection();
		Image* GetSprite();
		~RagDoll();
	};
}