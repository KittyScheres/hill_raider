#pragma once

#include "image.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The programming credits overlay class is used to initialize and 
	// keep track of the programming credits overlay for the game.
	// ------------------------------------------------------------
	class ProgrammingCreditsOverlay
	{
	private:
		Image* m_Screentitle = nullptr;
		Image* m_CppFastTrackCredits = nullptr;
		Image* m_SdlCredits = nullptr;
		Image* m_FreeImageCredits = nullptr;
		Image* m_AStarCredits = nullptr;
		Image* m_GameCodeCredits = nullptr;

	public:
		ProgrammingCreditsOverlay();
		void Render(Tmpl8::Surface* screen);
		~ProgrammingCreditsOverlay();
	};
}