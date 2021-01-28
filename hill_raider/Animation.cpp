#include "Animation.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the animation.
	// --------------------------------------------------
	Animation::Animation(char* srcPath, short iXFrames, short iYFrames, float iTimePerFrame, int iX, int iY, bool iLoop)
	{
		src = new Image(srcPath, iX, iY, iXFrames, iYFrames);
		xFrames = iXFrames;
		timePerFrame = iTimePerFrame;
		loop = iLoop;
	}

	// --------------------------------------------------
	// This method is used to update the animation.
	// --------------------------------------------------
	void Animation::UpdateAnimation(float deltaTime)
	{
		if (animationTimer >= timePerFrame) {
			if (currentXFrame < xFrames) {
				src->SetCurrentXFrame(++currentXFrame);
				animationTimer = 0.f;
			}
			else if (loop) {
				src->SetCurrentXFrame(0);
				currentXFrame = 0;
				animationTimer = 0.f;
			}
		}
		else {
			animationTimer += deltaTime;
		}
	}

	// --------------------------------------------------
	// This method is used to the animation on to the 
	// screen.
	// --------------------------------------------------
	void Animation::DrawAnimation(Tmpl8::Surface* screen)
	{
		src->DrawImage(screen);
	}

	// --------------------------------------------------
	// This method is used to set the position of the 
	// animation.
	// --------------------------------------------------
	void Animation::SetPosition(int iX, int iY)
	{
		src->SetPosition(iX, iY);
	}

	// --------------------------------------------------
	// This method is used to set the time per frame for
	// the animation.
	// --------------------------------------------------
	void Animation::SetTimePerFrame(float iTimePerFrame)
	{
		timePerFrame = iTimePerFrame;
	}

	// --------------------------------------------------
	// This method is used to update the current x axis
	// of the sampel frame from the animation source.
	// --------------------------------------------------
	void Animation::SetCurrentXFrame(short iCurrentXFrame)
	{
		currentXFrame = iCurrentXFrame;
		src->SetCurrentXFrame(iCurrentXFrame);
	}

	// --------------------------------------------------
	// This method is used to update the current y axis
	// of the sampel frame from the animation source.
	// --------------------------------------------------
	void Animation::SetCurrentYFrame(short iCurrentYFrame)
	{
		src->SetCurrentYFrame(iCurrentYFrame);
	}

	// --------------------------------------------------
	// This method is used to get the current position
	// the animation.
	// --------------------------------------------------
	std::vector<int> Animation::GetPosition()
	{
		return src->GetPosition();
	}

	// --------------------------------------------------
	// This method is used to get the display width of
	// the animation.
	// --------------------------------------------------
	int Animation::GetWidth()
	{
		return src->GetWidth();
	}

	// --------------------------------------------------
	// This method is used to get the display height of
	// the animation.
	// --------------------------------------------------
	int Animation::GetHeight()
	{
		return src->GetHeight();
	}

	// --------------------------------------------------
	// This deconstructor is used to safly free up the
	// memory of the animation source.
	// --------------------------------------------------
	Animation::~Animation()
	{
		if (src != nullptr) {
			delete src;
			src = nullptr;
		}
	}
}