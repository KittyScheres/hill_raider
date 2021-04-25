#pragma once

#include "image.h"
#include "scoreBoard.h"
#include "gameData.h"

namespace HillRaider
{
	// --------------------------------------------------
	// The ui class is used to initialize and keep track
	// of the ui for the game.
	// --------------------------------------------------
	class Ui
	{
	private:
		Image* m_HealingIcon = nullptr;
		Image* m_HealthBar[GameData::c_s_MaxHealth] = {};
		Image* m_FoodScoreIcon = nullptr;
		ScoreBoard* m_ScoreBoard = nullptr;

	public:
		Ui();
		void Render(Tmpl8::Surface* screen);
		~Ui();

	private:
		std::string GetPointsString();
		void ShowHealingIcon(Tmpl8::Surface* screen);
	};
}