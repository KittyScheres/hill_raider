#include "Animation.h"

namespace DownBelow
{
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	Animation::Animation(char* srcPath, unsigned int iFrames, float iTimePerFrame, bool iLoop, int iX, int iY)
	{
		src = new Tmpl8::Sprite(new Tmpl8::Surface(srcPath), iFrames);
		frames = iFrames;
		timePerFrame = iTimePerFrame;
		loop = iLoop;
		x = iX;
		y = iY;
		currentFrame = 0;
		src->SetFrame(currentFrame);
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Animation::UpdateAnimation(float deltaTime)
	{
		if (currentFrame < frames) {
			animationTimer += deltaTime;

			if (animationTimer >= timePerFrame) {
				currentFrame += 1;

				if (currentFrame >= frames && loop) {
					currentFrame = 0;
				}

				if (currentFrame < frames) {
					src->SetFrame(currentFrame);
					animationTimer = 0.f;
				}
			}
		}
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Animation::DrawAnimation(Tmpl8::Surface* screen)
	{
		src->Draw(screen, x, y);
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Animation::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	int* Animation::GetPosition()
	{
		int postion[2]{ x, y };
		return postion;
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
	unsigned int Animation::GetCurrentFrame()
	{
		return currentFrame;
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