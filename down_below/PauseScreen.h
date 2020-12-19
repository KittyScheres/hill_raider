#pragma once

#include "surface.h"

namespace HillRaider
{
	class PauseScreen
	{
	public:
		PauseScreen();
		void GamePause();
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~PauseScreen();
	};
}