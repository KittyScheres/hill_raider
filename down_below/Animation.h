#pragma once

#include "surface.h";

namespace DownBelow
{
	class Animation
	{
	private:
		Tmpl8::Sprite* src = nullptr;
		unsigned int frames = 0;
		float timePerFrame = 0.f;
		bool loop = false;
		int x = 0;
		int y = 0;
		float animationTimer = 0.f;
		unsigned int currentFrame = 0;

	public: 
		Animation(char* srcPath, unsigned int iFrames, float iTimePerFrame, bool iLoop, int iX, int iY);
		void UpdateAnimation(float deltaTime);
		void DrawAnimation(Tmpl8::Surface* screen);
		void SetPosition(int iX, int iY);
		int* GetPosition();
		int GetWidth();
		int GetHeight();
		unsigned int GetCurrentFrame();
		~Animation();
	};
}