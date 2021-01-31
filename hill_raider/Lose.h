#pragma once

#include "State.h"
#include "GameCallback.h"
#include "Image.h"
#include "InputManager.h"
#include "StartMenu.h"
#include "GamePlay.h"

namespace HillRaider
{
	// --------------------------------------------------
	// The lose state class is used to initialize and keep
	// track off everything on de lose screen of the game.
	// --------------------------------------------------
	class Lose: public State
	{
	private:
		GameCallback* callback = nullptr;
		Image* background = nullptr;
		Image* loseMessage = nullptr;
		Image* buttonBackground = nullptr;
		int buttonsXPos[2] { 2 * 64, 8 * 64 };
		Image* buttonHighlight = nullptr;
		Image* backToMenuButtonText = nullptr;
		Image* retryButtonText = nullptr;
		int selectedButton = 0;

	public:
		Lose(GameCallback* iCallback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~Lose();
	};
}