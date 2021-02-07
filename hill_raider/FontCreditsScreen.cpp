#include "FontCreditsScreen.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	FontCreditsScreen::FontCreditsScreen()
	{
		screenTitle = new Image("assets/text/font_credits_title.png", 0, 0);
		screenTitle->SetPosition(480 - (screenTitle->GetWidth() / 2), 32);

		fontCredits = new Image("assets/text/font_credits.png", 0, 0);
		fontCredits->SetPosition(480 - (fontCredits->GetWidth() / 2), 288 - (fontCredits->GetHeight() / 2));
	}

	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	void FontCreditsScreen::Render(Tmpl8::Surface* screen)
	{
		screenTitle->DrawImage(screen);
		fontCredits->DrawImage(screen);
	}

	// ------------------------------------------------------------
	// 
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