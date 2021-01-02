#include "StartMenu.h"

namespace HillRaider 
{
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	StartMenu::StartMenu(StateCallback* iCallback)
	{
		callback = iCallback;
		inputManager = InputManager::GetInstance();

		background = new Image("assets/ui/background.png", 0, 0);
		title = new Image("assets/ui/game_title.png", 4 * 64, 32);

		buttonBackground = new Image("assets/ui/menu_item_background.png", 5 * 64, menuButtonsY[0]);

		playGameButtonText = new Image("assets/ui/play_button_text.png", 5 * 64, menuButtonsY[0]);
		checkControlsButtonText = new Image("assets/ui/controls_button_text.png", 5 * 64, menuButtonsY[1]);
		exitGameButtonText = new Image("assets/ui/quit_button_text.png", 5 * 64, menuButtonsY[2]);

		menuItemHighlight = new Image("assets/ui/menu_item_highlight.png", 5 * 64, menuButtonsY[selectedMenuItem]);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void StartMenu::Update(float deltaTime)
	{
		if (inputManager->KeyPressed(InputManager::Keys::UP) && selectedMenuItem > 0) {
			--selectedMenuItem;
		}
		
		if (inputManager->KeyPressed(InputManager::Keys::DOWN) && selectedMenuItem < 2) {
			++selectedMenuItem;
		}

		if (inputManager->KeyPressed(InputManager::Keys::ENTER)) {
			switch (selectedMenuItem)
			{
			case 0:
				callback->SetNextState(new GamePlay(callback));
				break;

			case 1:
				
				break;

			case 2:
				callback->CloseGame();
				break;
			}
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void StartMenu::Render(Tmpl8::Surface* screen)
	{
		background->DrawImage(screen);
		title->DrawImage(screen);

		for (short i = 0; i < 3; i++) {
			buttonBackground->SetPosition(5 * 64, menuButtonsY[i]);
			buttonBackground->DrawImage(screen);
		}

		menuItemHighlight->SetPosition(5 * 64, menuButtonsY[selectedMenuItem]);
		menuItemHighlight->DrawImage(screen);

		playGameButtonText->DrawImage(screen);
		checkControlsButtonText->DrawImage(screen);
		exitGameButtonText->DrawImage(screen);
	}

	// --------------------------------------------------
	//
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