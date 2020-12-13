#pragma once

#include "Entity.h"
#include "Image.h"
#include "InputManager.h"

namespace DownBelow
{
	class Player : public Entity
	{
	private:
		InputManager* inputManager = nullptr;
		Image* playerSprite = nullptr;
		float speed = 0.f;
	public:
		Player(int iX, int iY, float iSpeed, int iWidth, int iHeight);
		void Update(float deltaTime);
		void LateUpdate(std::vector<Entity*> entityList);
		void Render(Tmpl8::Surface* screen);
		MovementDirection GetDirection();
		Image* GetSprite();
		~Player();
	private:
		void CheckForKeyPressed();
		void CheckForKeyLetGo();
		void MovePlayer(float deltaTime);
	};
}