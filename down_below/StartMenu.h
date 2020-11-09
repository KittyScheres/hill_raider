#pragma once

#include "State.h"
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
		StartMenu();
		void Update(float deltaTime);
		void LateUpdate();
		void Render(Tmpl8::Surface* screen);
		~StartMenu();

	private:
		Animation* tank = nullptr;
	};
}