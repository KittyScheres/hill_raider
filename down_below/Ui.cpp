#include "Ui.h"

namespace DownBelow
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Ui::Ui()
	{
		gameData = GameData::GetInstance();

		for (int i = 0; i < gameData->MAX_HEALTH; i++) {
			if (i % 2 == 0) {
				healthBar[i] = new Image("assets/gameplay/ui/half_heart_1.png", 64 * (1 + (i / 2)), 0);
			}
			else {
				healthBar[i] = new Image("assets/gameplay/ui/half_heart_2.png", 64 * (1 + (i / 2)), 0);
			}			
		}
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Ui::Render(Tmpl8::Surface* screen)
	{
		for (int i = 0; i < gameData->playerHealth; i++) {
			healthBar[i]->DrawImage(screen);
		}
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Ui::~Ui()
	{
		for (auto halfHeart : healthBar) {
			if (halfHeart != nullptr) {
				delete halfHeart;
				halfHeart = nullptr;
			}
		}

		gameData = nullptr;
	}
}