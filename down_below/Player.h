#pragma once

#include "Entity.h"
#include "RagDoll.h"
#include "Image.h"
#include "InputManager.h"
#include "GameData.h"

namespace DownBelow
{
	class Player : public Entity
	{
	private:
		const short attackHitboxWidth = 20;
		const short attackHitboxHeight = 10;
	private:
		InputManager* inputManager = nullptr;
		Image* playerSprite = nullptr;
		Hitbox* attackHitbox = nullptr;
		float speed = 0.f;
		short attackHitboxOffset = (height / 2) + (attackHitboxHeight / 2);
		bool attackFlag = false;
	public:
		Player(int iX, int iY, float iSpeed, int iWidth, int iHeight);
		void Update(float deltaTime);
		void LateUpdate(std::vector<Entity*> entityList);
		void Render(Tmpl8::Surface* screen);
		void TakeDamage();
		void SetPosition(int iX, int iY);
		void SetDirection(Entity::MovementDirection iDirection);
		MovementDirection GetDirection();
		Image* GetSprite();
		~Player();
	private:
		void CheckForKeyPressed();
		void CheckForKeyLetGo();
		void MovePlayer(float deltaTime);
	};
}