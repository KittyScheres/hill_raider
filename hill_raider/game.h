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
		void SetTarget(Surface* surface) { m_Screen = surface; }
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
		Surface* m_Screen;
		HillRaider::InputManager* m_InputManager = nullptr;
		HillRaider::State* m_CurrentState = nullptr;
		HillRaider::State* m_NextState = nullptr;
	};
};