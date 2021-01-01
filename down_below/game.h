#pragma once

#include "template.h"
#include "StateCallback.h"
#include "InputManager.h"

namespace Tmpl8
{
	class Surface;
	class Game : public HillRaider::StateCallback
	{
	public:
		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void SetState();
		void SetNextState(HillRaider::State* newState);
		void CloseGame();
		void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	private:
		Surface* screen;
		HillRaider::InputManager* inputManager = nullptr;
		HillRaider::State* currentState = nullptr;
		HillRaider::State* nextState = nullptr;
	};
}; // namespace Tmpl8