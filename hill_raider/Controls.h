#pragma once

#include "State.h"
#include "GameCallback.h"
#include "Image.h"
#include "InputManager.h"
#include "StartMenu.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// The controls state class is used to initialize and keep
	// track off everything on the controls screen.
	// ------------------------------------------------------------
	class Controls: public State
	{
	private:
		GameCallback* m_GameCallback = nullptr;
		Image* m_Background = nullptr;
		Image* m_ReturnToMenu = nullptr;
		Image* m_KeyBindings = nullptr;
		Image* m_LungeAttackExplanation = nullptr;
		Image* m_HealExplanation = nullptr;

	public:
		Controls(GameCallback* callback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~Controls();
	};
}