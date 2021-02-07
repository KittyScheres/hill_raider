#pragma once

#include "State.h"
#include "GameCallback.h"
#include "InputManager.h"
#include "StartMenu.h"
#include "ArtCreditsScreen.h"
#include "ProgrammingCreditsScreen.h"
#include "FontCreditsScreen.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The credits state class is used to initialize and keep
	// track off everything on the credits screen.
	// ------------------------------------------------------------
	class Credits: public State
	{
	private:
		GameCallback* callback = nullptr;
		Image* background = nullptr;
		Image* pressEnterMessage = nullptr;
		ArtCreditsScreen* artCredits = nullptr;
		ProgrammingCreditsScreen* programmingCredits = nullptr;
		FontCreditsScreen* fontCredits = nullptr;
		short currentScreen = 0;

	public:
		Credits(GameCallback* iCallback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~Credits();
	};
}