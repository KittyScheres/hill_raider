#pragma once

#include "image.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The font credits overlay class is used to initialize and 
	// keep track of the font credits overlay for the game.
	// ------------------------------------------------------------
	class FontCreditsOverlay
	{
	private:
		Image* m_ScreenTitle = nullptr;
		Image* m_FontCredits = nullptr;

	public:
		FontCreditsOverlay();
		void Render(Tmpl8::Surface* screen);
		~FontCreditsOverlay();
	};
}