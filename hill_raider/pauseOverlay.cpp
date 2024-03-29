#include "pauseOverlay.h"
#include "startMenu.h"
#include "gamePlay.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the components
	// of the pause overlay.
	// --------------------------------------------------
	PauseOverlay::PauseOverlay(GameCallback* callback)
	{
		m_InputManager = InputManager::GetInstance();
		m_GameCallback = callback;

		m_ButtonBackground = new Image("assets/ui/menu_item_background.png", 5 * 64, m_ButtonsYPos[0]);

		m_BackToMenuButtonText = new Image("assets/text/buttons/back_to_menu_button_text.png", 5 * 64, m_ButtonsYPos[0]);
		m_RestartGameButtonText = new Image("assets/text/buttons/restart_button_text.png", 5 * 64, m_ButtonsYPos[1]);

		m_ButtonHighlight = new Image("assets/ui/menu_item_highlight.png", 5 * 64, m_ButtonsYPos[0]);
	}

	// --------------------------------------------------
	// This method is used to reset the pause overlay object
	// when the game gets paused.
	// --------------------------------------------------
	void PauseOverlay::GamePause()
	{
		m_SelectedButton = 0;
	}

	// --------------------------------------------------
	// This method is used to update the components of
	// the pause overlay.
	// --------------------------------------------------
	void PauseOverlay::Update(float deltaTime)
	{
		// Check if the selector needs to be moved up
		if (m_InputManager->KeyPressed(KeyBinding::UP) && m_SelectedButton > 0) {
			--m_SelectedButton;
		}

		// Check if the selector need to be moved down
		if (m_InputManager->KeyPressed(KeyBinding::DOWN) && m_SelectedButton < 1) {
			++m_SelectedButton;
		}

		// Check if one of the list options has been selected
		if (m_InputManager->KeyPressed(KeyBinding::ENTER)) {
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
	// This method is used to draw the components of
	// the pause screen onto the screen.
	// --------------------------------------------------
	void PauseOverlay::Render(Tmpl8::Surface* screen)
	{
		for (short i = 0; i < 2; i++) {
			m_ButtonBackground->SetPosition(5 * 64, m_ButtonsYPos[i]);
			m_ButtonBackground->DrawImage(screen);
		}

		m_ButtonHighlight->SetPosition(5 * 64, m_ButtonsYPos[m_SelectedButton]);
		m_ButtonHighlight->DrawImage(screen);

		m_BackToMenuButtonText->DrawImage(screen);
		m_RestartGameButtonText->DrawImage(screen);
	}
	
	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// of the components of the pause overlay.
	// --------------------------------------------------
	PauseOverlay::~PauseOverlay()
	{
		if (m_ButtonBackground != nullptr) {
			delete m_ButtonBackground;
			m_ButtonBackground = nullptr;
		}

		if (m_BackToMenuButtonText != nullptr) {
			delete m_BackToMenuButtonText;
			m_BackToMenuButtonText = nullptr;
		}

		if (m_RestartGameButtonText != nullptr) {
			delete m_RestartGameButtonText;
			m_RestartGameButtonText = nullptr;
		}

		if (m_ButtonHighlight != nullptr) {
			delete m_ButtonHighlight;
			m_ButtonHighlight = nullptr;
		}
	}
}