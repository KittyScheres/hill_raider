#pragma once

#include "Image.h"
#include "InputManager.h"
#include "Hitbox.h"
#include <vector>
#include <cstdio>

namespace DownBelow
{
	class Player
	{
	public:
		enum class MovementDirection {UP = 0, RIGHT, DOWN, LEFT};
	private:
		InputManager* inputManager = nullptr;
		Image* playerSprite = nullptr;
		Hitbox* hitbox = nullptr;
		float speed = 0.f;
		MovementDirection direction = MovementDirection::UP;
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
	public:
		Player(int iX, int iY, float iSpeed, int iWidth, int iHeight);
		void Update(float deltaTime);
		void LateUpdate();
		void Render(Tmpl8::Surface* screen);
		void SetPosition(int iX, int iY);
		std::vector<int> GetPosition();
		MovementDirection GetDirection();
		int GetWidth();
		int GetHeight();
		Image* GetSprite();
		Hitbox* GetHitbox();
		~Player();
	private:
		void CheckForKeyPressed();
		void CheckForKeyLetGo();
		void MovePlayer(float deltaTime);
	};
}