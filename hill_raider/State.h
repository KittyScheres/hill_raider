#pragma once

#include "surface.h"

namespace HillRaider 
{
	// -------------------------------------------------------------------
	// The state is a template which can be used to create state classes.
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