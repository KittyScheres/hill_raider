#include "Ui.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the components
	// for the ui.
	// --------------------------------------------------
	Ui::Ui()
	{
		m_HealingIcon = new Image("assets/ui/healing_icon.png", 0, 0);
		m_HealingIcon->SetPosition(64 - m_HealingIcon->GetWidth(), 32 - (m_HealingIcon->GetHeight() / 2));

		for (short i = 0; i < GameData::GetInstance()->c_s_MaxHealth; i++) {
			if ((i & 1) == 0) {
				m_HealthBar[i] = new Image("assets/ui/half_heart_1.png", 64 * (1 + (i / 2)), 0);
			}
			else {
				m_HealthBar[i] = new Image("assets/ui/half_heart_2.png", 64 * (1 + (i / 2)), 0);
			}			
		}

		m_FoodScoreIcon = new Image("assets/entities/food_pickup.png", 0, 0);
		m_FoodScoreIcon->SetPosition((64 * 10) + 52, 32 - (m_FoodScoreIcon->GetHeight() / 2));

		m_ScoreBoard = new ScoreBoard();
		m_ScoreBoard->SetPosition((64 * 11) + 32, 32 - (m_ScoreBoard->GetHeightOfChar() / 2));
	}
	
	// --------------------------------------------------
	// This method is used to draw the ui on to the screen.
	// --------------------------------------------------
	void Ui::Render(Tmpl8::Surface* screen)
	{
		ShowHealingIcon(screen);

		for (short i = 0; i < GameData::GetInstance()->m_PlayerHealth; i++) {
			m_HealthBar[i]->DrawImage(screen);
		}

		m_FoodScoreIcon->DrawImage(screen);
		m_ScoreBoard->DrawScore(GetPointsString(), screen);
	}
	
	// --------------------------------------------------
	// This destructor is used to safely free the memory for
	// the components of the ui.
	// --------------------------------------------------
	Ui::~Ui()
	{
		if (m_HealingIcon != nullptr) {
			delete m_HealingIcon;
			m_HealingIcon = nullptr;
		}

		for (Image* halfHeart : m_HealthBar) {
			if (halfHeart != nullptr) {
				delete halfHeart;
				halfHeart = nullptr;
			}
		}

		if (m_FoodScoreIcon != nullptr) {
			delete m_FoodScoreIcon;
			m_FoodScoreIcon = nullptr;
		}

		if (m_ScoreBoard != nullptr) {
			delete m_ScoreBoard;
			m_ScoreBoard = nullptr;
		}
	}

	// --------------------------------------------------
	// This method is used to generate a points string which
	// will be displayed to the player.
	// --------------------------------------------------
	std::string Ui::GetPointsString() {
		std::string pointsString;
		std::string playerPoints = std::to_string(GameData::GetInstance()->m_PlayerPoints);
		
		for (short i = (short)playerPoints.size(); i < (short)std::to_string(GameData::c_s_MaxPoints).size(); i++) {
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
		if (gameDataInstance->m_PlayerHealth < gameDataInstance->c_s_MaxHealth && gameDataInstance->m_PlayerPoints >= gameDataInstance->c_s_PointsForHealth) {
			m_HealingIcon->DrawImage(screen);
		}
	}
}