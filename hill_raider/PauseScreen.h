#pragma once

#include "InputManager.h"
#include "GameCallback.h"
#include "Image.h"

namespace HillRaider
{
	// --------------------------------------------------
	// The pause screen class is used to initialize and 
	// keep track of the pause screen for the game.
	// --------------------------------------------------
	class PauseScreen
	{
	private:
		InputManager* m_InputManager = nullptr;
		GameCallback* m_GameCallback = nullptr;
		Image* m_ButtonBackground = nullptr;
		Image* m_BackToMenuButtonText = nullptr;
		Image* m_RestartGameButtonText = nullptr;
		int m_ButtonsYPos[2]{64 * 3, 64 * 5};
		short m_SelectedButton = 0;
		Image* m_ButtonHighlight = nullptr;

	public:
		PauseScreen(GameCallback* callback);
		void GamePause();
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~PauseScreen();
	};
}