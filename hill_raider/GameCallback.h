#pragma once

#include "state.h"

namespace HillRaider
{
	// -------------------------------------------------------------------
	// The game callback class contains methods which can be used by a 
	// state class to interact with the a game class instance.
	// -------------------------------------------------------------------
	class GameCallback
	{
	public:
		virtual void SetNextState(HillRaider::State* newState) {}
		virtual void CloseGame() {}
	};
}