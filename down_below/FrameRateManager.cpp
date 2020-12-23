#include "FrameRateManager.h"

namespace HillRaider
{
	void FrameRateManager::ResetFrameCapTimer()
	{
		frameCapTimer.reset();
	}

	void FrameRateManager::ConstrainFrameRate()
	{
		if (frameCapTimer.elapsed() < MILLISECCONDS_PER_FRAME)
		{
			SDL_Delay(MILLISECCONDS_PER_FRAME - frameCapTimer.elapsed());
		}
	}
}