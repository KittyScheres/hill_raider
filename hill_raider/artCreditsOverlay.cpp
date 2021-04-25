#include "artCreditsOverlay.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// This constructor is used to initialize the components of
	// the art credits overlay.
	// ------------------------------------------------------------
	ArtCreditsOverlay::ArtCreditsOverlay()
	{
		m_ScreenTitle = new Image("assets/text/titels/art_credits_title.png", 0, 0);
		m_ScreenTitle->SetPosition(480 - (m_ScreenTitle->GetWidth() / 2), 32);
		
		m_TileMapCredits = new Image("assets/text/credits/tilemap_credits.png", 0, 0);
		m_TileMapCredits->SetPosition(240 - (m_TileMapCredits->GetWidth() / 2), 64 + 32);

		m_ButtonsCredits = new Image("assets/text/credits/buttons_credits.png", 0, 0);
		m_ButtonsCredits->SetPosition(240 - (m_ButtonsCredits->GetWidth() / 2), 64 * 4);

		m_BackgroundCredits = new Image("assets/text/credits/background_credits.png", 0, 0);
		m_BackgroundCredits->SetPosition(240 - (m_BackgroundCredits->GetWidth() / 2), 64 * 6);

		m_FoodCredits = new Image("assets/text/credits/food_credits.png", 0, 0);
		m_FoodCredits->SetPosition(720 - (m_FoodCredits->GetWidth() / 2), 64 + 32);

		m_KeyboardKeysCredits = new Image("assets/text/credits/keyboard_keys_credits.png", 0, 0);
		m_KeyboardKeysCredits->SetPosition(720 - (m_KeyboardKeysCredits->GetWidth() / 2), 64 * 4);

		m_HeartsAntsCredits = new Image("assets/text/credits/hearts_ants_credits.png", 0, 0);
		m_HeartsAntsCredits->SetPosition(720 - (m_HeartsAntsCredits->GetWidth() / 2), 64 * 6);
	}

	// ------------------------------------------------------------
	// This method is used to draw the components onto the screen.
	// ------------------------------------------------------------
	void ArtCreditsOverlay::Render(Tmpl8::Surface* screen)
	{
		m_ScreenTitle->DrawImage(screen);
		m_TileMapCredits->DrawImage(screen);
		m_ButtonsCredits->DrawImage(screen);
		m_BackgroundCredits->DrawImage(screen);
		m_FoodCredits->DrawImage(screen);
		m_HeartsAntsCredits->DrawImage(screen);
		m_KeyboardKeysCredits->DrawImage(screen);
	}

	// ------------------------------------------------------------
	// This destructor is used to safely free the memory for the
	// components of the art credits overlay.
	// ------------------------------------------------------------
	ArtCreditsOverlay::~ArtCreditsOverlay()
	{
		if (m_ScreenTitle != nullptr) {
			delete m_ScreenTitle;
			m_ScreenTitle = nullptr;
		}

		if (m_TileMapCredits != nullptr) {
			delete m_TileMapCredits;
			m_TileMapCredits = nullptr;
		}

		if (m_ButtonsCredits != nullptr) {
			delete m_ButtonsCredits;
			m_ButtonsCredits = nullptr;
		}

		if (m_BackgroundCredits != nullptr) {
			delete m_BackgroundCredits;
			m_BackgroundCredits = nullptr;
		}

		if (m_FoodCredits != nullptr) {
			delete m_FoodCredits;
			m_FoodCredits = nullptr;
		}

		if (m_KeyboardKeysCredits != nullptr) {
			delete m_KeyboardKeysCredits;
			m_KeyboardKeysCredits = nullptr;
		}

		if (m_HeartsAntsCredits != nullptr) {
			delete m_HeartsAntsCredits;
			m_HeartsAntsCredits = nullptr;
		}
	}
}