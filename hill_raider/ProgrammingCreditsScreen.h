#pragma once

#include "Image.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The programming credits screen class is used to initialize and 
	// keep track of the programming credits screen for the game.
	// ------------------------------------------------------------
	class ProgrammingCreditsScreen
	{
	private:
		Image* screentitle = nullptr;
		Image* cppFastTrackCredits = nullptr;
		Image* sdlCredits = nullptr;
		Image* freeImageCredits = nullptr;
		Image* aStarCredits = nullptr;
		Image* gameCodeCredits = nullptr;

	public:
		ProgrammingCreditsScreen();
		void Render(Tmpl8::Surface* screen);
		~ProgrammingCreditsScreen();
	};
}