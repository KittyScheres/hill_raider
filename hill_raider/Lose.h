#pragma once

#include "state.h"
#include "gameCallback.h"
#include "image.h"
#include "inputManager.h"
#include "startMenu.h"
#include "gamePlay.h"

namespace HillRaider
{
	// --------------------------------------------------
	// The lose state class is used to initialize and keep
	// track of everything on the lose screen.
	// --------------------------------------------------
	class Lose: public State
	{
	private:
		GameCallback* m_GameCallback = nullptr;
		Image* m_Background = nullptr;
		Image* m_LoseMessage = nullptr;
		Image* m_ButtonBackground = nullptr;
		int m_ButtonsXPos[2] { 2 * 64, 8 * 64 };
		Image* m_ButtonHighlight = nullptr;
		Image* m_BackToMenuButtonText = nullptr;
		Image* m_RetryButtonText = nullptr;
		int m_SelectedButton = 0;

	public:
		Lose(GameCallback* callback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~Lose();
	};
}