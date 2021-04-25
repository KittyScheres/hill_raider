#pragma once

#include "image.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The art credits screen class is used to initialize and 
	// keep track of the art credits screen for the game.
	// ------------------------------------------------------------
	class ArtCreditsScreen
	{
	private:
		Image* m_ScreenTitle = nullptr;
		Image* m_TileMapCredits = nullptr;
		Image* m_ButtonsCredits = nullptr;
		Image* m_BackgroundCredits = nullptr;
		Image* m_FoodCredits = nullptr;
		Image* m_KeyboardKeysCredits = nullptr;
		Image* m_HeartsAntsCredits = nullptr;

	public:
		ArtCreditsScreen();
		void Render(Tmpl8::Surface* screen);
		~ArtCreditsScreen();
	};
}