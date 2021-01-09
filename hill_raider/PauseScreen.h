#pragma once

#include "InputManager.h"
#include "GameCallback.h"
#include "Image.h"

namespace HillRaider
{
	class PauseScreen
	{
	private:
		InputManager* inputManager = nullptr;
		GameCallback* callback = nullptr;

		Image* buttonBackground = nullptr;

		Image* backToMenuButtonText = nullptr;
		Image* restartGameButtonText = nullptr;
		int buttonsYPos[2]{64 * 3, 64 * 5};

		int selectedButton = 0;
		Image* buttonHighlight = nullptr;

	public:
		PauseScreen(GameCallback* iCallback);
		void GamePause();
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~PauseScreen();
	};
}