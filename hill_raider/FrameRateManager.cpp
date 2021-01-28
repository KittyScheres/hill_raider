#include "FrameRateManager.h"

namespace HillRaider
{
	// -----------------------------------------------------------
	// This method us used to reset the frame cap timer.
	// -----------------------------------------------------------
	void FrameRateManager::ResetFrameCapTimer()
	{
		frameCapTimer.reset();
	}

	// -----------------------------------------------------------
	// This method is used to artificialy increase the time per 
	// frame to decrease the frames per seccond.
	// -----------------------------------------------------------
	void FrameRateManager::ConstrainFrameRate()
	{
		if (frameCapTimer.elapsed() < MILLISECCONDS_PER_FRAME)
		{
			SDL_Delay((Uint32)(MILLISECCONDS_PER_FRAME - frameCapTimer.elapsed()));
		}
	}
}