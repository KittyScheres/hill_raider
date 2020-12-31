#pragma once

#include "RoomCallback.h"
#include "Entity.h"
#include "Player.h"
#include "Animation.h"
#include "AStar.h"
#include <random>

namespace HillRaider
{
	class RagDoll : public Entity
	{
	private:
		const short attackHitboxWidth = 20;
		const short attackHitboxHeight = 10;
		const short lineScanWidth = 2;
		const short lineScanHeight = 90;
		const short lungeSpeedIncrease = 200;
		const float makeDecisionCooldown = 1000.f;
		const float lungeDuration = 300.f;
		const float lungeCooldown = 2000.f;
	private:
		RoomCallback* callback = nullptr;
		Animation* legsAnimation = nullptr;
		Animation* bodyAnimation = nullptr;
		Hitbox* attackHitbox = nullptr;
		Hitbox* lineScan = nullptr;
		float speed = 0.f;
		int ragdollHealt = 2;
		short attackHitboxOffset = (height / 2) + (attackHitboxHeight / 2);
		short lineScanOffset = (height / 2) + (lineScanHeight / 2);
		bool makeDecisionFlag = false;
		bool lungeFlag = false;
		bool lungeCooldownFlag = false;
		float makeDecisionTimer = 0.f;
		float lungeDurationTimer = 0.f;
		float lungeCooldownTimer = 0.f;
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
		Animation* GetSprite();
		~RagDoll();
	private:
		void UpdateDirection();
		void MoveRagdoll(float deltaTime);
		void Lunge(float deltaTime);
	};
}