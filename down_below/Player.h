#pragma once

#include "Image.h"
#include "InputManager.h"
#include <cstdio>

namespace DownBelow
{
	class Player
	{
	private:
		InputManager* inputManager = nullptr;
		Image* playerSprite = nullptr;
		float speed = 0.f;
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
		int* GetPosition();
		int GetWidth();
		int GetHeight();
		~Player();
	};
}