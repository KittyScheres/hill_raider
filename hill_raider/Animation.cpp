#include "Animation.h"

namespace HillRaider
{
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	Animation::Animation(char* srcPath, short iXFrames, short iYFrames, float iTimePerFrame, int iX, int iY, bool iLoop)
	{
		src = new Image(srcPath, iX, iY, iXFrames, iYFrames);
		xFrames = iXFrames;
		timePerFrame = iTimePerFrame;
		loop = iLoop;
	}

	// --------------------------------------------------
	// 
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
	// 
	// --------------------------------------------------
	void Animation::DrawAnimation(Tmpl8::Surface* screen)
	{
		src->DrawImage(screen);
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Animation::SetPosition(int iX, int iY)
	{
		src->SetPosition(iX, iY);
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Animation::SetTimePerFrame(float iTimePerFrame)
	{
		timePerFrame = iTimePerFrame;
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Animation::SetCurrentXFrame(short iCurrentXFrame)
	{
		currentXFrame = iCurrentXFrame;
		src->SetCurrentXFrame(iCurrentXFrame);
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Animation::SetCurrentYFrame(short iCurrentYFrame)
	{
		src->SetCurrentYFrame(iCurrentYFrame);
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	int* Animation::GetPosition()
	{
		return src->GetPosition();
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	int Animation::GetWidth()
	{
		return src->GetWidth();
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	int Animation::GetHeight()
	{
		return src->GetHeight();
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	Animation::~Animation()
	{
		if (src != nullptr) {
			delete src;
			src = nullptr;
		}
	}
}