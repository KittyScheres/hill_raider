#include "Ui.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the components
	// for the ui.
	// --------------------------------------------------
	Ui::Ui()
	{
		healingIcon = new Image("assets/ui/healing_icon.png", 0, 0);
		healingIcon->SetPosition(64 - healingIcon->GetWidth(), 32 - (healingIcon->GetHeight() / 2));

		for (short i = 0; i < GameData::GetInstance()->MAX_HEALTH; i++) {
			if ((i & 1) == 0) {
				healthBar[i] = new Image("assets/ui/half_heart_1.png", 64 * (1 + (i / 2)), 0);
			}
			else {
				healthBar[i] = new Image("assets/ui/half_heart_2.png", 64 * (1 + (i / 2)), 0);
			}			
		}

		foodScoreIcon = new Image("assets/entities/food_pickup.png", 0, 0);
		foodScoreIcon->SetPosition((64 * 9) + 52, 32 - (foodScoreIcon->GetHeight() / 2));

		scoreBoard = new ScoreBoard();
		scoreBoard->SetPosition((64 * 10) + 32, 32 - (scoreBoard->GetHeightOfChar() / 2));
	}
	
	// --------------------------------------------------
	// This method is used to draw the ui on to the screen.
	// --------------------------------------------------
	void Ui::Render(Tmpl8::Surface* screen)
	{
		ShowHealingIcon(screen);

		for (short i = 0; i < GameData::GetInstance()->playerHealth; i++) {
			healthBar[i]->DrawImage(screen);
		}

		foodScoreIcon->DrawImage(screen);
		scoreBoard->DrawScore(GetPointsString(), screen);
	}
	
	// --------------------------------------------------
	// This destructor is used to safely free the memory for
	// the components of the ui.
	// --------------------------------------------------
	Ui::~Ui()
	{
		if (healingIcon != nullptr) {
			delete healingIcon;
			healingIcon = nullptr;
		}

		for (Image* halfHeart : healthBar) {
			if (halfHeart != nullptr) {
				delete halfHeart;
				halfHeart = nullptr;
			}
		}

		if (foodScoreIcon != nullptr) {
			delete foodScoreIcon;
			foodScoreIcon = nullptr;
		}

		if (scoreBoard != nullptr) {
			delete scoreBoard;
			scoreBoard = nullptr;
		}
	}

	// --------------------------------------------------
	// This method is used to generate a points string which
	// will be displayed to the player.
	// --------------------------------------------------
	std::string Ui::GetPointsString() {
		std::string pointsString;
		std::string playerPoints = std::to_string(GameData::GetInstance()->playerPoints);
		
		for (short i = (short)playerPoints.size(); i < (short)std::to_string(GameData::MAX_POINTS).size(); i++) {
			pointsString.push_back('0');
		}

		for (std::string::iterator points = playerPoints.begin(); points != playerPoints.end(); points++) {
			pointsString.push_back(*points);
		}
		
		return pointsString;
	}

	// --------------------------------------------------
	// This method is used to check if the healing icon 
	// needs to be displayed.
	// --------------------------------------------------
	void Ui::ShowHealingIcon(Tmpl8::Surface* screen)
	{
		GameData* gameDataInstance = GameData::GetInstance();
		if (gameDataInstance->playerHealth < gameDataInstance->MAX_HEALTH && gameDataInstance->playerPoints >= gameDataInstance->POINTS_FOR_HEALTH) {
			healingIcon->DrawImage(screen);
		}
	}
}