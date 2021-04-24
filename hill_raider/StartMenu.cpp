#include "StartMenu.h"

namespace HillRaider 
{
	// --------------------------------------------------
	// This constructor is used to initialize the components
	// for the start menu state.
	// --------------------------------------------------
	StartMenu::StartMenu(GameCallback* callback)
	{
		m_GameCallback = callback;
		m_InputManager = InputManager::GetInstance();

		m_Background = new Image("assets/ui/background.png", 0, 0);
		m_Title = new Image("assets/text/titels/game_title.png", 0, 0);
		m_Title->SetPosition(480 - (m_Title->GetWidth() / 2), 64);

		m_ButtonBackground = new Image("assets/ui/menu_item_background.png", 5 * 64, m_MenuButtonsY[0]);

		m_PlayGameButtonText = new Image("assets/text/buttons/play_button_text.png", 5 * 64, m_MenuButtonsY[0]);
		m_CheckControlsButtonText = new Image("assets/text/buttons/controls_button_text.png", 5 * 64, m_MenuButtonsY[1]);
		m_CreditsButtonText = new Image("assets/text/buttons/credits_button_text.png", 5 * 64, m_MenuButtonsY[2]);
		m_ExitGameButtonText = new Image("assets/text/buttons/quit_button_text.png", 5 * 64, m_MenuButtonsY[3]);

		m_MenuItemHighlight = new Image("assets/ui/menu_item_highlight.png", 5 * 64, m_MenuButtonsY[m_SelectedMenuItem]);
	}

	// --------------------------------------------------
	// This method is used to update the components on the
	// start menu.
	// --------------------------------------------------
	void StartMenu::Update(float deltaTime)
	{
		if (m_InputManager->KeyPressed(KeyBinding::UP) && m_SelectedMenuItem > 0) {
			--m_SelectedMenuItem;
		}
		
		if (m_InputManager->KeyPressed(KeyBinding::DOWN) && m_SelectedMenuItem < 3) {
			++m_SelectedMenuItem;
		}

		if (m_InputManager->KeyPressed(KeyBinding::ENTER)) {
			switch (m_SelectedMenuItem)
			{
			case 0:
				m_GameCallback->SetNextState(new Gameplay(m_GameCallback));
				break;

			case 1:
				m_GameCallback->SetNextState(new Controls(m_GameCallback));
				break;

			case 2:
				m_GameCallback->SetNextState(new Credits(m_GameCallback));
				break;

			case 3:
				m_GameCallback->CloseGame();
				break;
			}
		}
	}

	// --------------------------------------------------
	// This method is used to render all of the components
	// on the start menu.
	// --------------------------------------------------
	void StartMenu::Render(Tmpl8::Surface* screen)
	{
		m_Background->DrawImage(screen);
		m_Title->DrawImage(screen);

		for (int yPos: m_MenuButtonsY) {
			m_ButtonBackground->SetPosition(5 * 64, yPos);
			m_ButtonBackground->DrawImage(screen);
		}

		m_MenuItemHighlight->SetPosition(5 * 64, m_MenuButtonsY[m_SelectedMenuItem]);
		m_MenuItemHighlight->DrawImage(screen);

		m_PlayGameButtonText->DrawImage(screen);
		m_CheckControlsButtonText->DrawImage(screen);
		m_CreditsButtonText->DrawImage(screen);
		m_ExitGameButtonText->DrawImage(screen);
	}

	// --------------------------------------------------
	// This deconstructor is used to safely free the memory
	// of the components for the start menu.
	// --------------------------------------------------
	StartMenu::~StartMenu()
	{
		if (m_Background != nullptr) {
			delete m_Background;
			m_Background = nullptr;
		}

		if (m_Title != nullptr) {
			delete m_Title;
			m_Title = nullptr;
		}

		if (m_ButtonBackground != nullptr) {
			delete m_ButtonBackground;
			m_ButtonBackground = nullptr;
		}

		if (m_PlayGameButtonText != nullptr) {
			delete m_PlayGameButtonText;
			m_PlayGameButtonText = nullptr;
		}

		if (m_CheckControlsButtonText != nullptr) {
			delete m_CheckControlsButtonText;
			m_CheckControlsButtonText = nullptr;
		}

		if (m_CreditsButtonText != nullptr) {
			delete m_CreditsButtonText;
			m_CreditsButtonText = nullptr;
		}

		if (m_ExitGameButtonText != nullptr) {
			delete m_ExitGameButtonText;
			m_ExitGameButtonText = nullptr;
		}

		if (m_MenuItemHighlight != nullptr) {
			delete m_MenuItemHighlight;
			m_MenuItemHighlight = nullptr;
		}

		m_GameCallback = nullptr;
	}
}