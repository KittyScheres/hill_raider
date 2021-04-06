#include "FontCreditsScreen.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// This contructor is used to initialize the componenets for
	// the font credits screen.
	// ------------------------------------------------------------
	FontCreditsScreen::FontCreditsScreen()
	{
		screenTitle = new Image("assets/text/titels/font_credits_title.png", 0, 0);
		screenTitle->SetPosition(480 - (screenTitle->GetWidth() / 2), 32);

		fontCredits = new Image("assets/text/credits/font_credits.png", 0, 0);
		fontCredits->SetPosition(480 - (fontCredits->GetWidth() / 2), 288 - (fontCredits->GetHeight() / 2));
	}

	// ------------------------------------------------------------
	// This method is used to draw the components on to the screen.
	// ------------------------------------------------------------
	void FontCreditsScreen::Render(Tmpl8::Surface* screen)
	{
		screenTitle->DrawImage(screen);
		fontCredits->DrawImage(screen);
	}

	// ------------------------------------------------------------
	// This destructor is used to safely free the memory for the
	// components of the font credits screen.
	// ------------------------------------------------------------
	FontCreditsScreen::~FontCreditsScreen()
	{
		if (screenTitle != nullptr) {
			delete screenTitle;
			screenTitle = nullptr;
		}

		if (fontCredits != nullptr) {
			delete fontCredits;
			fontCredits = nullptr;
		}
	}
}