#include "FrameRateManager.h"

namespace HillRaider
{
	// -----------------------------------------------------------
	// This method us used to reset the frame cap timer.
	// -----------------------------------------------------------
	void FrameRateManager::ResetFrameCapTimer()
	{
		m_FrameCapTimer.reset();
	}

	// -----------------------------------------------------------
	// This method is used to artificialy increase the time per 
	// frame to decrease the frames per seccond.
	// -----------------------------------------------------------
	void FrameRateManager::ConstrainFrameRate()
	{
		if (m_FrameCapTimer.elapsed() < c_MillisecondsPerFrame)
		{
			SDL_Delay((Uint32)(c_MillisecondsPerFrame - m_FrameCapTimer.elapsed()));
		}
	}
}