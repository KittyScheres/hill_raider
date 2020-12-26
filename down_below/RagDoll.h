#pragma once

#include "RoomCallback.h"
#include "Entity.h"
#include "Player.h"
#include "Image.h"
#include "AStar.h"

namespace HillRaider
{
	class RagDoll : public Entity
	{
	private:
		const short attackHitboxWidth = 20;
		const short attackHitboxHeight = 10;
		const short lineScanWidth = 2;
		const short lineScanHeight = 90;
	private:
		RoomCallback* callback = nullptr;
		Image* ragDollSprite = nullptr;
		Hitbox* attackHitbox = nullptr;
		Hitbox* lineScan = nullptr;
		float speed = 0.f;
		int ragdollHealt = 2;
		short attackHitboxOffset = (height / 2) + (attackHitboxHeight / 2);
		short lineScanOffset = (height / 2) + (lineScanHeight / 2);
		bool attackFlag = false;
	public:
		RagDoll(int iX, int iY, float iSpeed, int iWidth, int iHeight);
		void Update(float deltaTime);
		void LateUpdate(std::list<Entity*> entityList);
		void Render(Tmpl8::Surface* screen);
		void TakeDamage();
		void SetRoomCallback(RoomCallback* iCallback);
		void SetPosition(int iX, int iY);
		void SetDirection(Entity::MovementDirection iDirection);
		MovementDirection GetDirection();
		Image* GetSprite();
		~RagDoll();
	private:
		void UpdateDirection();
		void MoveRagdoll(float deltaTime);
	};
}