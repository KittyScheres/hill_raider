#pragma once

#define FPS_GOAL 60

#include "SDL.h"
#include "template.h"

namespace HillRaider
{
	// -----------------------------------------------------------
	// This class contains methods for implementing a frames per
	// second cap.
	// -----------------------------------------------------------
	class FrameRateManager
	{
	private:
		const float c_MillisecondsPerFrame = 1000 / FPS_GOAL;
		Tmpl8::timer m_FrameCapTimer;

	public:
		void ResetFrameCapTimer();
		void ConstrainFrameRate();
	};
}