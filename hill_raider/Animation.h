#pragma once

#include "image.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to create and update an 
	// animation which can be drawn onto the screen.
	// --------------------------------------------------
	class Animation
	{
	private:
		Image* m_Source = nullptr;
		short m_XFrames = 0;
		short m_YFrames = 0;
		float m_TimePerFrame = 0.f;
		bool m_Loop = false;
		float m_AnimationTimer = 0.f;
		short m_CurrentXFrame = 0;

	public: 
		Animation(char* sourcePath, short xFrames, short yFrames, float timePerFrame, int x, int y, bool loop);
		void UpdateAnimation(float deltaTime);
		void DrawAnimation(Tmpl8::Surface* screen);
		void SetPosition(int x, int y);
		void SetTimePerFrame(float timePerFrame);
		void SetCurrentXFrame(short currentXFrame);
		void SetCurrentYFrame(short currentYFrame);
		std::vector<int> GetPosition();
		int GetWidth();
		int GetHeight();
		~Animation();
	};
}