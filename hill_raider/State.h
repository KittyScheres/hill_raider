#pragma once

#include "surface.h"

namespace HillRaider 
{
	// -------------------------------------------------------------------
	// The state class is a template which can be used to create state objects.
	// -------------------------------------------------------------------
	class State
	{
	public:
		virtual void SetupSingletons() {};
		virtual void Update(float deltaTime) {}
		virtual void LateUpdate() {}
		virtual void Render(Tmpl8::Surface* screen) {}
		virtual ~State() {}
	};
}