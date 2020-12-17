#pragma once

#include "State.h"

namespace DownBelow
{
	class StateCallback
	{
	public:
		virtual void SetState(DownBelow::State* newState) {}
		virtual void CloseGame() {}
	};
}