#pragma once

#include "Image.h";

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to create and update an 
	// animation which can be drawn on to the screen.
	// --------------------------------------------------
	class Animation
	{
	private:
		Image* src = nullptr;
		short xFrames = 0;
		short yFrames = 0;
		float timePerFrame = 0.f;
		bool loop = false;
		float animationTimer = 0.f;
		short currentXFrame = 0;

	public: 
		Animation(char* srcPath, short iXFrames, short iYFrames, float iTimePerFrame, int iX, int iY, bool iLoop);
		void UpdateAnimation(float deltaTime);
		void DrawAnimation(Tmpl8::Surface* screen);
		void SetPosition(int iX, int iY);
		void SetTimePerFrame(float iTimePerFrame);
		void SetCurrentXFrame(short iCurrentXFrame);
		void SetCurrentYFrame(short iCurrentYFrame);
		int* GetPosition();
		int GetWidth();
		int GetHeight();
		~Animation();
	};
}