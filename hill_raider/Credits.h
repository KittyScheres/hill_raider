#pragma once

#include "state.h"
#include "gameCallback.h"
#include "inputManager.h"
#include "startMenu.h"
#include "artCreditsOverlay.h"
#include "programmingCreditsOverlay.h"
#include "fontCreditsOverlay.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The credits state class is used to initialize and keep
	// track off everything on the credits screen.
	// ------------------------------------------------------------
	class Credits: public State
	{
	private:
		GameCallback* m_GameCallback = nullptr;
		Image* m_Background = nullptr;
		Image* m_PressEnterMessage = nullptr;
		ArtCreditsOverlay* m_ArtCredits = nullptr;
		ProgrammingCreditsOverlay* m_ProgrammingCredits = nullptr;
		FontCreditsOverlay* m_FontCredits = nullptr;
		short m_CurrentScreen = 0;

	public:
		Credits(GameCallback* callback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~Credits();
	};
}