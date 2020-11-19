#pragma once

#include "StateCallback.h"
#include "surface.h"
#include "Image.h"
#include "Animation.h"
#include "InputManager.h"
#include "GamePlay.h"
#include <cstdio>

namespace DownBelow 
{
	// ------------------------------------------------------------
	// Start menu is a state class. It detremens the functionality
	// of the games start menu.
	// ------------------------------------------------------------
	class StartMenu: public State
	{
	public:
		StartMenu(StateCallback* iCallback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~StartMenu();

	private:
		StateCallback* callback = nullptr;
		InputManager* inputManager = nullptr;

		Image* background = nullptr;
		Image* title = nullptr;

		int menuButtonsY[3] {4 * 64, (5 * 64) + 32 , 7 * 64};
		Image* playGameButtonBackground = nullptr;
		Image* checkControlsButtonBackground = nullptr;
		Image* exitGameButtonBackground = nullptr;
		
		Image* playGameButtonText = nullptr;
		Image* checkControlsButtonText = nullptr;
		Image* exitGameButtonText = nullptr;

		short selectedMenuItem = 0;
		Image* menuItemHighlight = nullptr;
	};
}