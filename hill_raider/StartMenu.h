#pragma once

#include "gameCallback.h"
#include "surface.h"
#include "image.h"
#include "animation.h"
#include "inputManager.h"
#include "gamePlay.h"
#include "controls.h"
#include "credits.h"

namespace HillRaider 
{
	// ------------------------------------------------------------
	// The start menu state class is used to initialize and keep
	// track of everything on the start menu screen.
	// ------------------------------------------------------------
	class StartMenu: public State
	{
	private:
		GameCallback* m_GameCallback = nullptr;
		InputManager* m_InputManager = nullptr;
		Image* m_Background = nullptr;
		Image* m_Title = nullptr;
		Image* m_ButtonBackground = nullptr;
		Image* m_PlayGameButtonText = nullptr;
		Image* m_CheckControlsButtonText = nullptr;
		Image* m_CreditsButtonText = nullptr;
		Image* m_ExitGameButtonText = nullptr;
		int m_MenuButtonsY[4]{ 4 * 64, 5 * 64, 6 * 64, 7 * 64 };
		short m_SelectedMenuItem = 0;
		Image* m_MenuItemHighlight = nullptr;

	public:
		StartMenu(GameCallback* callback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~StartMenu();
	};
}