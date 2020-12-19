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

		background = new Image("assets/title_screen/background.png", 0, 0);
		title = new Image("assets/title_screen/game_title.png", 4 * 64, 32);

		playGameButtonBackground = new Image("assets/title_screen/menu_item_background.png", 5 * 64, menuButtonsY[0]);
		checkControlsButtonBackground = new Image("assets/title_screen/menu_item_background.png", 5 * 64, menuButtonsY[1]);
		exitGameButtonBackground = new Image("assets/title_screen/menu_item_background.png", 5 * 64, menuButtonsY[2]);

		playGameButtonText = new Image("assets/title_screen/play_button_text.png", 5 * 64, menuButtonsY[0]);
		checkControlsButtonText = new Image("assets/title_screen/controls_button_text.png", 5 * 64, menuButtonsY[1]);
		exitGameButtonText = new Image("assets/title_screen/quit_button_text.png", 5 * 64, menuButtonsY[2]);

		menuItemHighlight = new Image("assets/title_screen/menu_item_highlight.png", 5 * 64, menuButtonsY[selectedMenuItem]);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void StartMenu::Update(float deltaTime)
	{
		if (inputManager->KeyPressed(InputManager::Keys::UP)) {
			if (selectedMenuItem > 0) {
				menuItemHighlight->SetPosition(5 * 64, menuButtonsY[--selectedMenuItem]);
			}
		}
		else if (inputManager->KeyPressed(InputManager::Keys::DOWN)) {
			if (selectedMenuItem < 2) {
				menuItemHighlight->SetPosition(5 * 64, menuButtonsY[++selectedMenuItem]);
			}
		}

		if (inputManager->KeyPressed(InputManager::Keys::ENTER)) {
			switch (selectedMenuItem)
			{
			case 0:
				callback->SetState(new GamePlay(callback));
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

		playGameButtonBackground->DrawImage(screen);
		checkControlsButtonBackground->DrawImage(screen);
		exitGameButtonBackground->DrawImage(screen);

		playGameButtonText->DrawImage(screen);
		checkControlsButtonText->DrawImage(screen);
		exitGameButtonText->DrawImage(screen);

		menuItemHighlight->DrawImage(screen);
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

		if (playGameButtonBackground != nullptr) {
			delete playGameButtonBackground;
			playGameButtonBackground = nullptr;
		}

		if (checkControlsButtonBackground != nullptr) {
			delete checkControlsButtonBackground;
			checkControlsButtonBackground = nullptr;
		}

		if (exitGameButtonBackground != nullptr) {
			delete exitGameButtonBackground;
			exitGameButtonBackground = nullptr;
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