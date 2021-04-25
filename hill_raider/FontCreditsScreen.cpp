#include "fontCreditsScreen.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// This contructor is used to initialize the componenets for
	// the font credits screen.
	// ------------------------------------------------------------
	FontCreditsScreen::FontCreditsScreen()
	{
		m_ScreenTitle = new Image("assets/text/titels/font_credits_title.png", 0, 0);
		m_ScreenTitle->SetPosition(480 - (m_ScreenTitle->GetWidth() / 2), 32);

		m_FontCredits = new Image("assets/text/credits/font_credits.png", 0, 0);
		m_FontCredits->SetPosition(480 - (m_FontCredits->GetWidth() / 2), 288 - (m_FontCredits->GetHeight() / 2));
	}

	// ------------------------------------------------------------
	// This method is used to draw the components on to the screen.
	// ------------------------------------------------------------
	void FontCreditsScreen::Render(Tmpl8::Surface* screen)
	{
		m_ScreenTitle->DrawImage(screen);
		m_FontCredits->DrawImage(screen);
	}

	// ------------------------------------------------------------
	// This destructor is used to safely free the memory for the
	// components of the font credits screen.
	// ------------------------------------------------------------
	FontCreditsScreen::~FontCreditsScreen()
	{
		if (m_ScreenTitle != nullptr) {
			delete m_ScreenTitle;
			m_ScreenTitle = nullptr;
		}

		if (m_FontCredits != nullptr) {
			delete m_FontCredits;
			m_FontCredits = nullptr;
		}
	}
}