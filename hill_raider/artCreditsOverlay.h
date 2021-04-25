#pragma once

#include "image.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The art credits overlay class is used to initialize and 
	// keep track of the art credits overlay for the game.
	// ------------------------------------------------------------
	class ArtCreditsOverlay
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
		ArtCreditsOverlay();
		void Render(Tmpl8::Surface* screen);
		~ArtCreditsOverlay();
	};
}