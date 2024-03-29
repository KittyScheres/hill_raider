#pragma once

#include "state.h"
#include "gameCallback.h"
#include "scoreBoard.h"
#include "inputManager.h"
#include "startMenu.h"
#include "gamePlay.h"

namespace HillRaider
{
	// --------------------------------------------------
	// The win state class is used to initialize and keep
	// track of everything on the win screen.
	// --------------------------------------------------
	class Win: public State
	{
	private:
		GameCallback* m_GameCallback = nullptr;
		Image* m_Background = nullptr;
		Image* m_WinTextStatic = nullptr;
		std::string m_Score = "";
		ScoreBoard* m_PlayerScore = nullptr;
		Image* m_WinTextDynamic = nullptr;
		Image* m_ButtonBackground = nullptr;
		int m_ButtonsXPos[2]{ 2 * 64, 8 * 64 };
		Image* m_ButtonHighlight = nullptr;
		Image* m_BackToMenuButtonText = nullptr;
		Image* m_RetryButtonText = nullptr;
		int m_SelectedButton = 0;

	public:
		Win(GameCallback* callback, int score);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~Win();

	private:
		void SetDynamicWinText(int score);
	};
}