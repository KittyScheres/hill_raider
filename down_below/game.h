#pragma once

#include "StateCallback.h"

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
		void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
		void KeyUp( int key ) { /* implement if you want to handle keys */ }
		void KeyDown( int key ) { /* implement if you want to handle keys */ }
	private:
		Surface* screen;
		DownBelow::State* currentState;
	};
}; // namespace Tmpl8