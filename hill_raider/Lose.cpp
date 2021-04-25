#include "lose.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties 
	// for the lose screen.
	// --------------------------------------------------
	Lose::Lose(GameCallback* callback)
	{
		m_GameCallback = callback;
		m_Background = new Image("assets/ui/background.png", 0, 0);
		
		m_LoseMessage = new Image("assets/text/lose_message.png", 0, 0);
		m_LoseMessage->SetPosition(480 - (m_LoseMessage->GetWidth() / 2), 70);

		m_ButtonBackground = new Image("assets/ui/menu_item_background.png", m_ButtonsXPos[0], 7 * 64);
		m_ButtonHighlight = new Image("assets/ui/menu_item_highlight.png", m_ButtonsXPos[m_SelectedButton], 7 * 64);

		m_BackToMenuButtonText = new Image("assets/text/buttons/back_to_menu_button_text.png", m_ButtonsXPos[0], 7 * 64);
		m_RetryButtonText = new Image("assets/text/buttons/try_again_button_text.png", m_ButtonsXPos[1], 7 * 64);
	}
	
	// --------------------------------------------------
	// This method is used to update the components on
	// the lose screen.
	// --------------------------------------------------
	void Lose::Update(float deltaTime)
	{
		if (m_SelectedButton > 0 && InputManager::GetInstance()->KeyPressed(KeyBinding::LEFT)) {
			--m_SelectedButton;
		}

		if (m_SelectedButton < 1 && InputManager::GetInstance()->KeyPressed(KeyBinding::RIGHT)) {
			++m_SelectedButton;
		}

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
	// lose screen on to the screen.
	// --------------------------------------------------
	void Lose::Render(Tmpl8::Surface* screen)
	{
		m_Background->DrawImage(screen);
		m_LoseMessage->DrawImage(screen);

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
	// of the components of the lose screen.
	// --------------------------------------------------
	Lose::~Lose()
	{
		if (m_Background != nullptr) {
			delete m_Background;
			m_Background = nullptr;
		}

		if (m_LoseMessage != nullptr) {
			delete m_LoseMessage;
			m_LoseMessage = nullptr;
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
}