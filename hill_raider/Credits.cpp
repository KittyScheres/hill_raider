#include "credits.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// This method is used to set up the components for the credits
	// state.
	// ------------------------------------------------------------
	Credits::Credits(GameCallback* callback)
	{
		m_GameCallback = callback;
		
		m_Background = new Image("assets/ui/background.png", 0, 0);
		m_PressEnterMessage = new Image("assets/text/press_enter_to_continue.png", 64 * 11, 64 * 8);
		m_ArtCredits = new ArtCreditsScreen();
		m_ProgrammingCredits = new ProgrammingCreditsScreen();
		m_FontCredits = new FontCreditsScreen();
	}
	
	// ------------------------------------------------------------
	// This method is used to update the components of the credits
	// state.
	// ------------------------------------------------------------
	void Credits::Update(float deltaTime)
	{
		// Check if the next credits screen needs to be displayed
		if (InputManager::GetInstance()->KeyPressed(KeyBinding::ENTER)) {
			// Check if all of the credits screens have been shown
			if (m_CurrentScreen++ >= 2) {
				m_GameCallback->SetNextState(new StartMenu(m_GameCallback));
			}
		}
	}
	
	// ------------------------------------------------------------
	// This method is used to draw the components of the credits
	// state onto the screen.
	// ------------------------------------------------------------
	void Credits::Render(Tmpl8::Surface* screen)
	{
		m_Background->DrawImage(screen);
		m_PressEnterMessage->DrawImage(screen);

		switch (m_CurrentScreen)
		{
		case 0:
			m_ArtCredits->Render(screen);
			break;

		case 1:
			m_ProgrammingCredits->Render(screen);
			break;

		case 2:
			m_FontCredits->Render(screen);
			break;
		}
	}
	
	// ------------------------------------------------------------
	// This destructor is used to safely free the memory of the 
	// components of the credits state.
	// ------------------------------------------------------------
	Credits::~Credits()
	{
		if (m_Background != nullptr) {
			delete m_Background;
			m_Background = nullptr;
		}

		if (m_PressEnterMessage != nullptr) {
			delete m_PressEnterMessage;
			m_PressEnterMessage = nullptr;
		}

		if (m_ArtCredits != nullptr) {
			delete m_ArtCredits;
			m_ArtCredits = nullptr;
		}

		if (m_ProgrammingCredits != nullptr) {
			delete m_ProgrammingCredits;
			m_ProgrammingCredits = nullptr;
		}

		if (m_FontCredits != nullptr) {
			delete m_FontCredits;
			m_FontCredits = nullptr;
		}

		m_GameCallback = nullptr;
	}
}