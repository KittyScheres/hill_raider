#pragma once

#include "Entity.h"
#include "RagDoll.h"
#include "Animation.h"
#include "InputManager.h"
#include "GameData.h"

namespace HillRaider
{
	class Player : public Entity
	{
	private:
		const short attackHitboxWidth = 20;
		const short attackHitboxHeight = 10;
		const short lungeSpeedIncrease = 200;
		const float lungeDuration = 200.f;
		const float lungeCooldown = 2000.f;
	private:
		InputManager* inputManager = nullptr;
		Animation* legsAnimation = nullptr;
		Animation* bodyAnimation = nullptr;
		Hitbox* attackHitbox = nullptr;
		float speed = 0.f;
		short attackHitboxOffset = (height / 2) + (attackHitboxHeight / 2);
		bool lungeFlag = false;
		bool lungeCooldownFlag = false;
		float lungeDurationTimer = 0.f;
		float lungeCooldownTimer = 0.f;
	public:
		Player(int iX, int iY, float iSpeed, int iWidth, int iHeight);
		void Update(float deltaTime);
		void LateUpdate(std::list<Entity*> entityList);
		void Render(Tmpl8::Surface* screen);
		void TakeDamage();
		void SetPosition(int iX, int iY);
		void SetDirection(Entity::MovementDirection iDirection);
		MovementDirection GetDirection();
		Animation* GetSprite();
		~Player();
	private:
		void CheckForKeyPressed();
		void CheckForKeyLetGo();
		void MovePlayer(float deltaTime);
		void Lunge(float deltaTime);
	};
}