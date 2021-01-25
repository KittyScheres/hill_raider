#pragma once

#include "Image.h"
#include "ScoreBoard.h"
#include "GameData.h"

namespace HillRaider
{
	// --------------------------------------------------
	// The ui class is used to initialize and keep track
	// of the ui for the game.
	// --------------------------------------------------
	class Ui
	{
	private:
		Image* healingIcon = nullptr;
		Image* healthBar[GameData::MAX_HEALTH];
		Image* foodScoreIcon = nullptr;
		ScoreBoard* scoreBoard = nullptr;

	public:
		Ui();
		void Render(Tmpl8::Surface* screen);
		~Ui();

	private:
		std::string GetPointsString();
		void ShowHealingIcon(Tmpl8::Surface* screen);
	};
}