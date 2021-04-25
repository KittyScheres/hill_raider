#pragma once

#include "image.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The font credits screen class is used to initialize and 
	// keep track of the font credits screen for the game.
	// ------------------------------------------------------------
	class FontCreditsScreen
	{
	private:
		Image* m_ScreenTitle = nullptr;
		Image* m_FontCredits = nullptr;

	public:
		FontCreditsScreen();
		void Render(Tmpl8::Surface* screen);
		~FontCreditsScreen();
	};
}