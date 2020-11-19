#pragma once

#include "surface.h"

namespace DownBelow
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