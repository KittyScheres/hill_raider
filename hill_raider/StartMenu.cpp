#include "StartMenu.h"

namespace HillRaider 
{
	// --------------------------------------------------
	// This constructor is used to initialize the components
	// for the start menu state.
	// --------------------------------------------------
	StartMenu::StartMenu(GameCallback* iCallback)
	{
		callback = iCallback;
		inputManager = InputManager::GetInstance();

		background = new Image("assets/ui/background.png", 0, 0);
		title = new Image("assets/text/game_title.png", 0, 0);
		title->SetPosition(480 - (title->GetWidth() / 2), 64);

		buttonBackground = new Image("assets/ui/menu_item_background.png", 5 * 64, menuButtonsY[0]);

		playGameButtonText = new Image("assets/text/play_button_text.png", 5 * 64, menuButtonsY[0]);
		checkControlsButtonText = new Image("assets/text/controls_button_text.png", 5 * 64, menuButtonsY[1]);
		creditsButtonText = new Image("assets/text/credits_button_text.png", 5 * 64, menuButtonsY[2]);
		exitGameButtonText = new Image("assets/text/quit_button_text.png", 5 * 64, menuButtonsY[3]);

		menuItemHighlight = new Image("assets/ui/menu_item_highlight.png", 5 * 64, menuButtonsY[selectedMenuItem]);
	}

	// --------------------------------------------------
	// This method is used to update the components on the
	// start menu.
	// --------------------------------------------------
	void StartMenu::Update(float deltaTime)
	{
		if (inputManager->KeyPressed(InputManager::Keys::UP) && selectedMenuItem > 0) {
			--selectedMenuItem;
		}
		
		if (inputManager->KeyPressed(InputManager::Keys::DOWN) && selectedMenuItem < 3) {
			++selectedMenuItem;
		}

		if (inputManager->KeyPressed(InputManager::Keys::ENTER)) {
			switch (selectedMenuItem)
			{
			case 0:
				callback->SetNextState(new GamePlay(callback));
				break;

			case 1:
				callback->SetNextState(new Controls(callback));
				break;

			case 2:
				callback->SetNextState(new Credits(callback));
				break;

			case 3:
				callback->CloseGame();
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
		background->DrawImage(screen);
		title->DrawImage(screen);

		for (int yPos: menuButtonsY) {
			buttonBackground->SetPosition(5 * 64, yPos);
			buttonBackground->DrawImage(screen);
		}

		menuItemHighlight->SetPosition(5 * 64, menuButtonsY[selectedMenuItem]);
		menuItemHighlight->DrawImage(screen);

		playGameButtonText->DrawImage(screen);
		checkControlsButtonText->DrawImage(screen);
		creditsButtonText->DrawImage(screen);
		exitGameButtonText->DrawImage(screen);
	}

	// --------------------------------------------------
	// This deconstructor is used to safely free the memory
	// of the components for the start menu.
	// --------------------------------------------------
	StartMenu::~StartMenu()
	{
		if (background != nullptr) {
			delete background;
			background = nullptr;
		}

		if (title != nullptr) {
			delete title;
			title = nullptr;
		}

		if (buttonBackground != nullptr) {
			delete buttonBackground;
			buttonBackground = nullptr;
		}

		if (playGameButtonText != nullptr) {
			delete playGameButtonText;
			playGameButtonText = nullptr;
		}

		if (checkControlsButtonText != nullptr) {
			delete checkControlsButtonText;
			checkControlsButtonText = nullptr;
		}

		if (creditsButtonText != nullptr) {
			delete creditsButtonText;
			creditsButtonText = nullptr;
		}

		if (exitGameButtonText != nullptr) {
			delete exitGameButtonText;
			exitGameButtonText = nullptr;
		}

		if (menuItemHighlight != nullptr) {
			delete menuItemHighlight;
			menuItemHighlight = nullptr;
		}

		callback = nullptr;
	}
}