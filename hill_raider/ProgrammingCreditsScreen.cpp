#include "ProgrammingCreditsScreen.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// This contructor is used to initialize the componenets for
	// the programming credits screen.
	// ------------------------------------------------------------
	ProgrammingCreditsScreen::ProgrammingCreditsScreen()
	{
		screentitle = new Image("assets/text/programming_credits_title.png", 0, 0);
		screentitle->SetPosition(480 - (screentitle->GetWidth() / 2), 32);

		cppFastTrackCredits = new Image("assets/text/template_credits.png", 0, 0);
		cppFastTrackCredits->SetPosition(480 - (cppFastTrackCredits->GetWidth() / 2), 64 + 32);

		sdlCredits = new Image("assets/text/sdl2_credits.png", 0, 0);
		sdlCredits->SetPosition(480 - (sdlCredits->GetWidth() / 2), 32 + (64 * 3));

		freeImageCredits = new Image("assets/text/free_image_credits.png", 0, 0);
		freeImageCredits->SetPosition(480 - (freeImageCredits->GetWidth() / 2), 64 * 5);


		aStarCredits = new Image("assets/text/a_star_credits.png", 0, 0);
		aStarCredits->SetPosition(480 - (aStarCredits->GetWidth() / 2), 32 + (64 * 6));
	}

	// ------------------------------------------------------------
	// This method is used to draw the components on to the screen.
	// ------------------------------------------------------------
	void ProgrammingCreditsScreen::Render(Tmpl8::Surface* screen)
	{
		screentitle->DrawImage(screen);
		cppFastTrackCredits->DrawImage(screen);
		sdlCredits->DrawImage(screen);
		freeImageCredits->DrawImage(screen);
		aStarCredits->DrawImage(screen);
	}

	// ------------------------------------------------------------
	// This destructor is used to safely free the memory for the
	// components of the programming credits screen.
	// ------------------------------------------------------------
	ProgrammingCreditsScreen::~ProgrammingCreditsScreen()
	{
		if (screentitle != nullptr) {
			delete screentitle;
			screentitle = nullptr;
		}

		if (cppFastTrackCredits != nullptr) {
			delete cppFastTrackCredits;
			cppFastTrackCredits = nullptr;
		}

		if (sdlCredits != nullptr) {
			delete sdlCredits;
			sdlCredits = nullptr;
		}

		if (freeImageCredits != nullptr) {
			delete freeImageCredits;
			freeImageCredits = nullptr;
		}

		if (aStarCredits != nullptr) {
			delete aStarCredits;
			aStarCredits = nullptr;
		}
	}
}