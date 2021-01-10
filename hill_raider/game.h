#pragma once

#include "template.h"
#include "GameCallback.h"
#include "InputManager.h"

namespace Tmpl8
{
	class Surface;
	class Game : public HillRaider::GameCallback
	{
	public:
		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void SetState();
		void SetNextState(HillRaider::State* newState);
		void CloseGame();
		void MouseUp( int button ) {}
		void MouseDown( int button ) {}
		void MouseMove( int x, int y ) {}

	private:
		Surface* screen;
		HillRaider::InputManager* inputManager = nullptr;
		HillRaider::State* currentState = nullptr;
		HillRaider::State* nextState = nullptr;
	};
};