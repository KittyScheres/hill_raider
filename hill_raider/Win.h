#pragma once

#include "State.h"
#include "GameCallback.h"
#include "ScoreBoard.h"
#include "InputManager.h"
#include "StartMenu.h"
#include "GamePlay.h"

namespace HillRaider
{
	// --------------------------------------------------
	// The win state class is used to initialize and keep
	// track off everything on the win screen.
	// --------------------------------------------------
	class Win: public State
	{
	private:
		GameCallback* callback = nullptr;
		Image* background = nullptr;
		Image* winTextStatic = nullptr;
		std::string score = "";
		ScoreBoard* playerScore = nullptr;
		Image* winTextDynamic = nullptr;
		Image* buttonBackground = nullptr;
		int buttonsXPos[2]{ 2 * 64, 8 * 64 };
		Image* buttonHighlight = nullptr;
		Image* backToMenuButtonText = nullptr;
		Image* retryButtonText = nullptr;
		int selectedButton = 0;

	public:
		Win(GameCallback* iCallback, int iScore);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~Win();

	private:
		void SetDynamicWinText(int iScore);
	};
}