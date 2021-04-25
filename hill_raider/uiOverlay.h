#pragma once

#include "image.h"
#include "scoreBoard.h"
#include "gameData.h"

namespace HillRaider
{
	// --------------------------------------------------
	// The UI overlay class is used to initialize and keep track
	// of the UI for the game.
	// --------------------------------------------------
	class UiOverlay
	{
	private:
		Image* m_HealingIcon = nullptr;
		Image* m_HealthBar[GameData::c_s_MaxHealth] = {};
		Image* m_FoodScoreIcon = nullptr;
		ScoreBoard* m_ScoreBoard = nullptr;

	public:
		UiOverlay();
		void Render(Tmpl8::Surface* screen);
		~UiOverlay();

	private:
		std::string GetPointsString();
		void ShowHealingIcon(Tmpl8::Surface* screen);
	};
}