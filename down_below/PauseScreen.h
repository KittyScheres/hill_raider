#pragma once

#include "InputManager.h"
#include "StateCallback.h"
#include "Image.h"

namespace HillRaider
{
	class PauseScreen
	{
	private:
		InputManager* inputManager = nullptr;
		StateCallback* callback = nullptr;

		Image* buttonBackground = nullptr;

		Image* backToMenuButtonText = nullptr;
		Image* restartGameButtonText = nullptr;
		int buttonsYPos[2]{64 * 3, 64 * 5};

		int selectedButton = 0;
		Image* buttonHighlight = nullptr;

	public:
		PauseScreen(StateCallback* iCallback);
		void GamePause();
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~PauseScreen();
	};
}