#pragma once

#include "StateCallback.h"
#include "surface.h"
#include "Image.h"
#include "Animation.h"

namespace DownBelow 
{
	// ------------------------------------------------------------
	// Start menu is a state class. It detremens the functionality
	// of the games start menu.
	// ------------------------------------------------------------
	class StartMenu: public State
	{
	public:
		StartMenu(StateCallback* iCallback);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		~StartMenu();

	private:
		StateCallback* callback = nullptr;
		Animation* tank = nullptr;
		float timer = 0.f;
	};
}