#pragma once

#include "State.h"

namespace HillRaider
{
	class StateCallback
	{
	public:
		virtual void SetState(HillRaider::State* newState) {}
		virtual void CloseGame() {}
	};
}