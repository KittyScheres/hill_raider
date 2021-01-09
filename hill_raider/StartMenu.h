#pragma once

#include "GameCallback.h"
#include "surface.h"
#include "Image.h"
#include "Animation.h"
#include "InputManager.h"
#include "GamePlay.h"
#include <cstdio>

namespace HillRaider 
{
	// ------------------------------------------------------------
	// Start menu is a state class. It detremens the functionality
	// of the games start menu.
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
		Image* exitGameButtonText = nullptr;
		int menuButtonsY[3]{ 4 * 64, (5 * 64) + 32 , 7 * 64 };

		short selectedMenuItem = 0;
		Image* menuItemHighlight = nullptr;

	public:
		StartMenu(GameCallback* iCallback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~StartMenu();
	};
}