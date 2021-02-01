#pragma once

#include "State.h"
#include "GameCallback.h"
#include "Image.h"
#include "InputManager.h"
#include "StartMenu.h"

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

	public:
		Credits(GameCallback* iCallback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~Credits();
	};
}