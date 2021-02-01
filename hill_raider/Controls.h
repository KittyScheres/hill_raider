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
		GameCallback* callback = nullptr;
		Image* background = nullptr;
		Image* returnToMenu = nullptr;
		Image* keyBindings = nullptr;
		Image* lungeAttackExplanation = nullptr;
		Image* healExplanation = nullptr;

	public:
		Controls(GameCallback* iCallback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~Controls();
	};
}