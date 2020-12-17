#pragma once

#include "StateCallback.h"
#include "InputManager.h"

namespace Tmpl8
{
	class Surface;
	class Game : public DownBelow::StateCallback
	{
	public:
		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void SetState(DownBelow::State* newState);
		void CloseGame();
		void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	private:
		Surface* screen;
		DownBelow::InputManager* inputManager = nullptr;
		DownBelow::State* currentState = nullptr;
	};
}; // namespace Tmpl8