#include "Win.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the components 
	// for the win screen.
	// --------------------------------------------------
	Win::Win(GameCallback* iCallback, int iScore)
	{
		callback = iCallback;
		background = new Image("assets/ui/background.png", 0, 0);

		winTextStatic = new Image("assets/text/win_message_static_text.png", 0, 0);
		winTextStatic->SetPosition(480 - (winTextStatic->GetWidth() / 2), 70);

		score = std::to_string(iScore);
		playerScore = new ScoreBoard();
		playerScore->SetPosition(480 - ((playerScore->GetWidthOfChar() * score.size()) / 2), 220);

		SetDynamicWinText(iScore);
		winTextDynamic->SetPosition(480 - (winTextDynamic->GetWidth() / 2), 290);

		buttonBackground = new Image("assets/ui/menu_item_background.png", buttonsXPos[0], 7 * 64);
		buttonHighlight = new Image("assets/ui/menu_item_highlight.png", buttonsXPos[selectedButton], 7 * 64);

		backToMenuButtonText = new Image("assets/text/back_to_menu_button_text.png", buttonsXPos[0], 7 * 64);
		retryButtonText = new Image("assets/text/try_again_button_text.png", buttonsXPos[1], 7 * 64);
	}

	// --------------------------------------------------
	// This method is used to update the components for
	// the game screen.
	// --------------------------------------------------
	void Win::Update(float deltaTime)
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
				callback->SetNextState(new GamePlay(callback));
				break;
			}
		}
	}

	// --------------------------------------------------
	// This method is used to draw the components for the
	// win screen on to the screen.
	// --------------------------------------------------
	void Win::Render(Tmpl8::Surface* screen)
	{
		background->DrawImage(screen);
		winTextStatic->DrawImage(screen);
		playerScore->DrawScore(score, screen);
		winTextDynamic->DrawImage(screen);

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
	// for the components of the win screen.
	// --------------------------------------------------
	Win::~Win()
	{
		if (background != nullptr) {
			delete background;
			background = nullptr;
		}

		if (winTextStatic != nullptr) {
			delete winTextStatic;
			winTextStatic = nullptr;
		}

		if (playerScore != nullptr) {
			delete playerScore;
			playerScore = nullptr;
		}

		if (winTextDynamic != nullptr) {
			delete winTextDynamic;
			winTextDynamic = nullptr;
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

	// --------------------------------------------------
	// This method is used to set the dynamic text according
	// to the the score of the player.
	// --------------------------------------------------
	void Win::SetDynamicWinText(int iScore)
	{
		if (iScore < 500) {
			winTextDynamic = new Image("assets/text/win_text_dynamic_too_little.png", 0, 0);
		}
		else if (iScore < 1000) {
			winTextDynamic = new Image("assets/text/win_text_dynamic_enough.png", 0, 0);
		}
		else {
			winTextDynamic = new Image("assets/text/win_text_dynamic_more_than_enough.png", 0, 0);
		}
	}
}