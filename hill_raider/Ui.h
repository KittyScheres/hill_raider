#pragma once

#include "Image.h"
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
		Image* healthBar[GameData::MAX_HEALTH];

	public:
		Ui();
		void Render(Tmpl8::Surface* screen);
		~Ui();
	};
}