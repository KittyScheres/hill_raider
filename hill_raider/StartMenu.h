#pragma once

#include "GameCallback.h"
#include "surface.h"
#include "Image.h"
#include "Animation.h"
#include "InputManager.h"
#include "GamePlay.h"
#include "Controls.h"

namespace HillRaider 
{
	// ------------------------------------------------------------
	// The start menu state class is used to initialize and keep
	// track off everything on de start menu of the game.
	// ------------------------------------------------------------
	class StartMenu: public State
	{
	private:
		GameCallback* callback = nullptr;
		InputManager* inputManager = nullptr;
		Image* background = nullptr;
		Image* title = nullptr;
		Image* buttonBackground = nullptr;
		Image* playGameButtonText = nullptr;
		Image* checkControlsButtonText = nullptr;
		Image* creditsButtonText = nullptr;
		Image* exitGameButtonText = nullptr;
		int menuButtonsY[4]{ 4 * 64, 5 * 64, 6 * 64, 7 * 64 };
		short selectedMenuItem = 0;
		Image* menuItemHighlight = nullptr;

	public:
		StartMenu(GameCallback* iCallback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~StartMenu();
	};
}