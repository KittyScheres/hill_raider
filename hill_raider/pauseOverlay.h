#pragma once

#include "inputManager.h"
#include "gameCallback.h"
#include "image.h"

namespace HillRaider
{
	// --------------------------------------------------
	// The pause overlay class is used to initialize and 
	// keep track of the pause overlay for the game.
	// --------------------------------------------------
	class PauseOverlay
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
		PauseOverlay(GameCallback* callback);
		void GamePause();
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~PauseOverlay();
	};
}