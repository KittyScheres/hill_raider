#pragma once

#define FPS_GOAL 70

#include "SDL.h"
#include "template.h"

namespace HillRaider
{
	class FrameRateManager
	{
	private:
		const int MILLISECCONDS_PER_FRAME = 1000 / FPS_GOAL;
		Tmpl8::timer frameCapTimer;

	public:
		void ResetFrameCapTimer();
		void ConstrainFrameRate();
	};
}