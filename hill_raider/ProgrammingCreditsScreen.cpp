#include "programmingCreditsScreen.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// This constructor is used to initialize the components of
	// the programming credits screen.
	// ------------------------------------------------------------
	ProgrammingCreditsScreen::ProgrammingCreditsScreen()
	{
		m_Screentitle = new Image("assets/text/titels/programming_credits_title.png", 0, 0);
		m_Screentitle->SetPosition(480 - (m_Screentitle->GetWidth() / 2), 32);

		m_CppFastTrackCredits = new Image("assets/text/credits/template_credits.png", 0, 0);
		m_CppFastTrackCredits->SetPosition(240 - (m_CppFastTrackCredits->GetWidth() / 2), 64 + 32);

		m_AStarCredits = new Image("assets/text/credits/a_star_credits.png", 0, 0);
		m_AStarCredits->SetPosition(240 - (m_AStarCredits->GetWidth() / 2), 64 * 6);

		m_SdlCredits = new Image("assets/text/credits/sdl2_credits.png", 0, 0);
		m_SdlCredits->SetPosition(720 - (m_SdlCredits->GetWidth() / 2), 64 + 32);

		m_FreeImageCredits = new Image("assets/text/credits/free_image_credits.png", 0, 0);
		m_FreeImageCredits->SetPosition(720 - (m_FreeImageCredits->GetWidth() / 2), 64 * 4);

		m_GameCodeCredits = new Image("assets/text/credits/game_code_credits.png", 0, 0);
		m_GameCodeCredits->SetPosition(720 - (m_GameCodeCredits->GetWidth() / 2), 64 * 6);

	}

	// ------------------------------------------------------------
	// This method is used to draw the components onto the screen.
	// ------------------------------------------------------------
	void ProgrammingCreditsScreen::Render(Tmpl8::Surface* screen)
	{
		m_Screentitle->DrawImage(screen);
		m_CppFastTrackCredits->DrawImage(screen);
		m_AStarCredits->DrawImage(screen);
		m_SdlCredits->DrawImage(screen);
		m_FreeImageCredits->DrawImage(screen);
		m_GameCodeCredits->DrawImage(screen);
	}

	// ------------------------------------------------------------
	// This destructor is used to safely free the memory for the
	// components of the programming credits screen.
	// ------------------------------------------------------------
	ProgrammingCreditsScreen::~ProgrammingCreditsScreen()
	{
		if (m_Screentitle != nullptr) {
			delete m_Screentitle;
			m_Screentitle = nullptr;
		}

		if (m_CppFastTrackCredits != nullptr) {
			delete m_CppFastTrackCredits;
			m_CppFastTrackCredits = nullptr;
		}

		if (m_AStarCredits != nullptr) {
			delete m_AStarCredits;
			m_AStarCredits = nullptr;
		}

		if (m_SdlCredits != nullptr) {
			delete m_SdlCredits;
			m_SdlCredits = nullptr;
		}

		if (m_FreeImageCredits != nullptr) {
			delete m_FreeImageCredits;
			m_FreeImageCredits = nullptr;
		}

		if (m_GameCodeCredits != nullptr) {
			delete m_GameCodeCredits;
			m_GameCodeCredits = nullptr;
		}
	}
}