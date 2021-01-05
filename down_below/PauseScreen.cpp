#include "PauseScreen.h"
#include "StartMenu.h"
#include "GamePlay.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	PauseScreen::PauseScreen(StateCallback* iCallback)
	{
		inputManager = InputManager::GetInstance();
		callback = iCallback;

		buttonBackground = new Image("assets/ui/menu_item_background.png", 5 * 64, buttonsYPos[0]);

		backToMenuButtonText = new Image("assets/ui/back_to_menu_button_text.png", 5 * 64, buttonsYPos[0]);
		restartGameButtonText = new Image("assets/ui/restart_button_text.png", 5 * 64, buttonsYPos[1]);

		buttonHighlight = new Image("assets/ui/menu_item_highlight.png", 5 * 64, buttonsYPos[0]);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void PauseScreen::GamePause()
	{
		selectedButton = 0;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void PauseScreen::Update(float deltaTime)
	{
		if (inputManager->KeyPressed(InputManager::Keys::UP) && selectedButton > 0) {
			--selectedButton;
		}

		if (inputManager->KeyPressed(InputManager::Keys::DOWN) && selectedButton < 1) {
			++selectedButton;
		}

		if (inputManager->KeyPressed(InputManager::Keys::ENTER)) {
			switch (selectedButton)
			{
			case 0:
				callback->SetNextState(new StartMenu(callback));
				break;

			case 1:
				callback->SetNextState(new GamePlay(callback));
				break;
			}
		}
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	void PauseScreen::Render(Tmpl8::Surface* screen)
	{
		for (short i = 0; i < 2; i++) {
			buttonBackground->SetPosition(5 * 64, buttonsYPos[i]);
			buttonBackground->DrawImage(screen);
		}

		buttonHighlight->SetPosition(5 * 64, buttonsYPos[selectedButton]);
		buttonHighlight->DrawImage(screen);

		backToMenuButtonText->DrawImage(screen);
		restartGameButtonText->DrawImage(screen);
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	PauseScreen::~PauseScreen()
	{
		if (buttonBackground != nullptr) {
			delete buttonBackground;
			buttonBackground = nullptr;
		}

		if (backToMenuButtonText != nullptr) {
			delete backToMenuButtonText;
			backToMenuButtonText = nullptr;
		}

		if (restartGameButtonText != nullptr) {
			delete restartGameButtonText;
			restartGameButtonText = nullptr;
		}

		if (buttonHighlight != nullptr) {
			delete buttonHighlight;
			buttonHighlight = nullptr;
		}
	}
}