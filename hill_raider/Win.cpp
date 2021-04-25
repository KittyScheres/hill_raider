#include "win.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to set up the components 
	// for the win screen.
	// --------------------------------------------------
	Win::Win(GameCallback* callback, int score)
	{
		m_GameCallback = callback;
		m_Background = new Image("assets/ui/background.png", 0, 0);

		m_WinTextStatic = new Image("assets/text/win_message_static_text.png", 0, 0);
		m_WinTextStatic->SetPosition(480 - (m_WinTextStatic->GetWidth() / 2), 70);

		m_Score = std::to_string(score);
		m_PlayerScore = new ScoreBoard();
		m_PlayerScore->SetPosition(480 - ((m_PlayerScore->GetWidthOfChar() * m_Score.size()) / 2), 220);

		SetDynamicWinText(score);
		m_WinTextDynamic->SetPosition(480 - (m_WinTextDynamic->GetWidth() / 2), 290);

		m_ButtonBackground = new Image("assets/ui/menu_item_background.png", m_ButtonsXPos[0], 7 * 64);
		m_ButtonHighlight = new Image("assets/ui/menu_item_highlight.png", m_ButtonsXPos[m_SelectedButton], 7 * 64);

		m_BackToMenuButtonText = new Image("assets/text/buttons/back_to_menu_button_text.png", m_ButtonsXPos[0], 7 * 64);
		m_RetryButtonText = new Image("assets/text/buttons/try_again_button_text.png", m_ButtonsXPos[1], 7 * 64);
	}

	// --------------------------------------------------
	// This method is used to update the components of
	// the game screen.
	// --------------------------------------------------
	void Win::Update(float deltaTime)
	{
		// Check if the selector needs to be moved to the left
		if (m_SelectedButton > 0 && InputManager::GetInstance()->KeyPressed(KeyBinding::LEFT)) {
			--m_SelectedButton;
		}

		//  Check if the selector needs to be moved to the right
		if (m_SelectedButton < 1 && InputManager::GetInstance()->KeyPressed(KeyBinding::RIGHT)) {
			++m_SelectedButton;
		}

		// Check if one of the list options has been selected
		if (InputManager::GetInstance()->KeyPressed(KeyBinding::ENTER)) {
			switch (m_SelectedButton)
			{
			case 0:
				m_GameCallback->SetNextState(new StartMenu(m_GameCallback));
				break;

			case 1:
				m_GameCallback->SetNextState(new Gameplay(m_GameCallback));
				break;
			}
		}
	}

	// --------------------------------------------------
	// This method is used to draw the components of the
	// win screen onto the screen.
	// --------------------------------------------------
	void Win::Render(Tmpl8::Surface* screen)
	{
		m_Background->DrawImage(screen);
		m_WinTextStatic->DrawImage(screen);
		m_PlayerScore->DrawScore(m_Score, screen);
		m_WinTextDynamic->DrawImage(screen);

		for (int xPos : m_ButtonsXPos) {
			m_ButtonBackground->SetPosition(xPos, 7 * 64);
			m_ButtonBackground->DrawImage(screen);
		}

		m_ButtonHighlight->SetPosition(m_ButtonsXPos[m_SelectedButton], 7 * 64);
		m_ButtonHighlight->DrawImage(screen);

		m_BackToMenuButtonText->DrawImage(screen);
		m_RetryButtonText->DrawImage(screen);
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// for the components of the win screen.
	// --------------------------------------------------
	Win::~Win()
	{
		if (m_Background != nullptr) {
			delete m_Background;
			m_Background = nullptr;
		}

		if (m_WinTextStatic != nullptr) {
			delete m_WinTextStatic;
			m_WinTextStatic = nullptr;
		}

		if (m_PlayerScore != nullptr) {
			delete m_PlayerScore;
			m_PlayerScore = nullptr;
		}

		if (m_WinTextDynamic != nullptr) {
			delete m_WinTextDynamic;
			m_WinTextDynamic = nullptr;
		}

		if (m_ButtonBackground != nullptr) {
			delete m_ButtonBackground;
			m_ButtonBackground = nullptr;
		}

		if (m_ButtonHighlight != nullptr) {
			delete m_ButtonHighlight;
			m_ButtonHighlight = nullptr;
		}

		if (m_BackToMenuButtonText != nullptr) {
			delete m_BackToMenuButtonText;
			m_BackToMenuButtonText = nullptr;
		}

		if (m_RetryButtonText != nullptr) {
			delete m_RetryButtonText;
			m_RetryButtonText = nullptr;
		}

		m_GameCallback = nullptr;
	}

	// --------------------------------------------------
	// This method is used to set the dynamic text according
	// to the the score of the player.
	// --------------------------------------------------
	void Win::SetDynamicWinText(int score)
	{
		if (score < 500) {
			m_WinTextDynamic = new Image("assets/text/win_text_dynamic_too_little.png", 0, 0);
		}
		else if (score < 1000) {
			m_WinTextDynamic = new Image("assets/text/win_text_dynamic_enough.png", 0, 0);
		}
		else {
			m_WinTextDynamic = new Image("assets/text/win_text_dynamic_more_than_enough.png", 0, 0);
		}
	}
}