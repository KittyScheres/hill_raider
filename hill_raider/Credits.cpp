#include "Credits.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	Credits::Credits(GameCallback* iCallback)
	{
		callback = iCallback;
		
		background = new Image("assets/ui/background.png", 0, 0);
		pressEnterMessage = new Image("assets/text/press_enter_to_continue.png", 64 * 11, 64 * 8);
		artCredits = new ArtCreditsScreen();
		programmingCredits = new ProgrammingCreditsScreen();
		fontCredits = new FontCreditsScreen();
	}
	
	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	void Credits::Update(float deltaTime)
	{
		if (InputManager::GetInstance()->KeyPressed(InputManager::Keys::ENTER)) {
			if (currentScreen++ >= 2) {
				callback->SetNextState(new StartMenu(callback));
			}
		}
	}
	
	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	void Credits::Render(Tmpl8::Surface* screen)
	{
		background->DrawImage(screen);
		pressEnterMessage->DrawImage(screen);

		switch (currentScreen)
		{
		case 0:
			artCredits->Render(screen);
			break;

		case 1:
			programmingCredits->Render(screen);
			break;

		case 2:
			fontCredits->Render(screen);
			break;
		}
	}
	
	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	Credits::~Credits()
	{
		if (background != nullptr) {
			delete background;
			background = nullptr;
		}

		if (pressEnterMessage != nullptr) {
			delete pressEnterMessage;
			pressEnterMessage = nullptr;
		}

		if (artCredits != nullptr) {
			delete artCredits;
			artCredits = nullptr;
		}

		if (programmingCredits != nullptr) {
			delete programmingCredits;
			programmingCredits = nullptr;
		}

		if (fontCredits != nullptr) {
			delete fontCredits;
			fontCredits = nullptr;
		}

		callback = nullptr;
	}
}