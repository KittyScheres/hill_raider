#include "Ui.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the components
	// for the ui.
	// --------------------------------------------------
	Ui::Ui()
	{
		for (short i = 0; i < GameData::GetInstance()->MAX_HEALTH; i++) {
			if ((i & 1) == 0) {
				healthBar[i] = new Image("assets/ui/half_heart_1.png", 64 * (1 + (i / 2)), 0);
			}
			else {
				healthBar[i] = new Image("assets/ui/half_heart_2.png", 64 * (1 + (i / 2)), 0);
			}			
		}
	}
	
	// --------------------------------------------------
	// This method is used to draw the ui on to the screen.
	// --------------------------------------------------
	void Ui::Render(Tmpl8::Surface* screen)
	{
		for (short i = 0; i < GameData::GetInstance()->playerHealth; i++) {
			healthBar[i]->DrawImage(screen);
		}
	}
	
	// --------------------------------------------------
	// This destructor is used to safely free the memory for
	// the components of the ui.
	// --------------------------------------------------
	Ui::~Ui()
	{
		for (Image* halfHeart : healthBar) {
			if (halfHeart != nullptr) {
				delete halfHeart;
				halfHeart = nullptr;
			}
		}
	}
}