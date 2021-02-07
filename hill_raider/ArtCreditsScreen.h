#pragma once

#include "Image.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The art credits screen class is used to initialize and 
	// keep track of the art credits screen for the game.
	// ------------------------------------------------------------
	class ArtCreditsScreen
	{
	private:
		Image* screenTitle = nullptr;
		Image* tileMapCredits = nullptr;
		Image* buttonsCredits = nullptr;
		Image* backgroundCredits = nullptr;
		Image* foodCredits = nullptr;
		Image* keyboardKeysCredits = nullptr;

	public:
		ArtCreditsScreen();
		void Render(Tmpl8::Surface* screen);
		~ArtCreditsScreen();
	};
}