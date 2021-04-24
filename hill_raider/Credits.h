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
		GameCallback* m_GameCallback = nullptr;
		Image* m_Background = nullptr;
		Image* m_PressEnterMessage = nullptr;
		ArtCreditsScreen* m_ArtCredits = nullptr;
		ProgrammingCreditsScreen* m_ProgrammingCredits = nullptr;
		FontCreditsScreen* m_FontCredits = nullptr;
		short m_CurrentScreen = 0;

	public:
		Credits(GameCallback* callback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~Credits();
	};
}