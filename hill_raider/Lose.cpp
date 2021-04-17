#include "Lose.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties 
	// for the lose screen.
	// --------------------------------------------------
	Lose::Lose(GameCallback* iCallback)
	{
		callback = iCallback;
		background = new Image("assets/ui/background.png", 0, 0);
		
		loseMessage = new Image("assets/text/lose_message.png", 0, 0);
		loseMessage->SetPosition(480 - (loseMessage->GetWidth() / 2), 70);

		buttonBackground = new Image("assets/ui/menu_item_background.png", buttonsXPos[0], 7 * 64);
		buttonHighlight = new Image("assets/ui/menu_item_highlight.png", buttonsXPos[selectedButton], 7 * 64);

		backToMenuButtonText = new Image("assets/text/buttons/back_to_menu_button_text.png", buttonsXPos[0], 7 * 64);
		retryButtonText = new Image("assets/text/buttons/try_again_button_text.png", buttonsXPos[1], 7 * 64);
	}
	
	// --------------------------------------------------
	// This method is used to update the components on
	// the lose screen.
	// --------------------------------------------------
	void Lose::Update(float deltaTime)
	{
		if (selectedButton > 0 && InputManager::GetInstance()->KeyPressed(InputManager::Keys::LEFT)) {
			--selectedButton;
		}

		if (selectedButton < 1 && InputManager::GetInstance()->KeyPressed(InputManager::Keys::RIGHT)) {
			++selectedButton;
		}

		if (InputManager::GetInstance()->KeyPressed(InputManager::Keys::ENTER)) {
			switch (selectedButton)
			{
			case 0:
				callback->SetNextState(new StartMenu(callback));
				break;
			
			case 1:
				callback->SetNextState(new Gameplay(callback));
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
		background->DrawImage(screen);
		loseMessage->DrawImage(screen);

		for (int xPos : buttonsXPos) {
			buttonBackground->SetPosition(xPos, 7 * 64);
			buttonBackground->DrawImage(screen);
		}

		buttonHighlight->SetPosition(buttonsXPos[selectedButton], 7 * 64);
		buttonHighlight->DrawImage(screen);

		backToMenuButtonText->DrawImage(screen);
		retryButtonText->DrawImage(screen);
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// of the components of the lose screen.
	// --------------------------------------------------
	Lose::~Lose()
	{
		if (background != nullptr) {
			delete background;
			background = nullptr;
		}

		if (loseMessage != nullptr) {
			delete loseMessage;
			loseMessage = nullptr;
		}

		if (buttonBackground != nullptr) {
			delete buttonBackground;
			buttonBackground = nullptr;
		}

		if (buttonHighlight != nullptr) {
			delete buttonHighlight;
			buttonHighlight = nullptr;
		}

		if (backToMenuButtonText != nullptr) {
			delete backToMenuButtonText;
			backToMenuButtonText = nullptr;
		}

		if (retryButtonText != nullptr) {
			delete retryButtonText;
			retryButtonText = nullptr;
		}

		callback = nullptr;
	}
}