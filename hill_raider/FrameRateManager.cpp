#include "FrameRateManager.h"

namespace HillRaider
{
	// -----------------------------------------------------------
	// This mehtod us used to reset the frame cap timer.
	// -----------------------------------------------------------
	void FrameRateManager::ResetFrameCapTimer()
	{
		frameCapTimer.reset();
	}

	// -----------------------------------------------------------
	// This mehtod is used to artificialy increase the time per 
	// frame to decrease the frames per seccond.
	// -----------------------------------------------------------
	void FrameRateManager::ConstrainFrameRate()
	{
		if (frameCapTimer.elapsed() < MILLISECCONDS_PER_FRAME)
		{
			SDL_Delay(MILLISECCONDS_PER_FRAME - frameCapTimer.elapsed());
		}
	}
}