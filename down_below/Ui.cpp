#include "Ui.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Ui::Ui()
	{
		for (int i = 0; i < GameData::GetInstance()->MAX_HEALTH; i++) {
			if (i % 2 == 0) {
				healthBar[i] = new Image("assets/ui/half_heart_1.png", 64 * (1 + (i / 2)), 0);
			}
			else {
				healthBar[i] = new Image("assets/ui/half_heart_2.png", 64 * (1 + (i / 2)), 0);
			}			
		}
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Ui::Render(Tmpl8::Surface* screen)
	{
		for (int i = 0; i < GameData::GetInstance()->playerHealth; i++) {
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
	}
}