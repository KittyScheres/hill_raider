#include "ArtCreditsScreen.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// This contructor is used to initialize the componenets for
	// the art credits screen.
	// ------------------------------------------------------------
	ArtCreditsScreen::ArtCreditsScreen()
	{
		screenTitle = new Image("assets/text/art_credits_title.png", 0, 0);
		screenTitle->SetPosition(480 - (screenTitle->GetWidth() / 2), 32);
		
		tileMapCredits = new Image("assets/text/tilemap_credits.png", 0, 0);
		tileMapCredits->SetPosition(480 - (tileMapCredits->GetWidth() / 2), 64 + 32);

		buttonsCredits = new Image("assets/text/buttons_credits.png", 0, 0);
		buttonsCredits->SetPosition(480 - (buttonsCredits->GetWidth() / 2), 52 + (64 * 2));

		backgroundCredits = new Image("assets/text/background_credits.png", 0, 0);
		backgroundCredits->SetPosition(480 - (backgroundCredits->GetWidth() / 2), 12 + (64 * 4));

		foodCredits = new Image("assets/text/food_credits.png", 0, 0);
		foodCredits->SetPosition(480 - (foodCredits->GetWidth() / 2), 32 + (64 * 5));

		keyboardKeysCredits = new Image("assets/text/keyboard_keys_credits.png", 0, 0);
		keyboardKeysCredits->SetPosition(480 - (keyboardKeysCredits->GetWidth() / 2), 54 + (64 * 6));
	}

	// ------------------------------------------------------------
	// This method is used to draw the components on to the screen.
	// ------------------------------------------------------------
	void ArtCreditsScreen::Render(Tmpl8::Surface* screen)
	{
		screenTitle->DrawImage(screen);
		tileMapCredits->DrawImage(screen);
		buttonsCredits->DrawImage(screen);
		backgroundCredits->DrawImage(screen);
		foodCredits->DrawImage(screen);
		keyboardKeysCredits->DrawImage(screen);
	}

	// ------------------------------------------------------------
	// This destructor is used to safely free the memory for the
	// components of the art credits screen.
	// ------------------------------------------------------------
	ArtCreditsScreen::~ArtCreditsScreen()
	{
		if (screenTitle != nullptr) {
			delete screenTitle;
			screenTitle = nullptr;
		}

		if (tileMapCredits != nullptr) {
			delete tileMapCredits;
			tileMapCredits = nullptr;
		}

		if (buttonsCredits != nullptr) {
			delete buttonsCredits;
			buttonsCredits = nullptr;
		}

		if (backgroundCredits != nullptr) {
			delete backgroundCredits;
			backgroundCredits = nullptr;
		}

		if (foodCredits != nullptr) {
			delete foodCredits;
			foodCredits != nullptr;
		}

		if (keyboardKeysCredits != nullptr) {
			delete keyboardKeysCredits;
			keyboardKeysCredits = nullptr;
		}
	}
}