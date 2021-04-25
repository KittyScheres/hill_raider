#pragma once

#include "image.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The programming credits screen class is used to initialize and 
	// keep track of the programming credits screen for the game.
	// ------------------------------------------------------------
	class ProgrammingCreditsScreen
	{
	private:
		Image* m_Screentitle = nullptr;
		Image* m_CppFastTrackCredits = nullptr;
		Image* m_SdlCredits = nullptr;
		Image* m_FreeImageCredits = nullptr;
		Image* m_AStarCredits = nullptr;
		Image* m_GameCodeCredits = nullptr;

	public:
		ProgrammingCreditsScreen();
		void Render(Tmpl8::Surface* screen);
		~ProgrammingCreditsScreen();
	};
}