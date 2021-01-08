#pragma once

#include "State.h"

namespace HillRaider
{
	class StateCallback
	{
	public:
		virtual void SetNextState(HillRaider::State* newState) {}
		virtual void CloseGame() {}
	};
}