#pragma once

#include "surface.h"
#include <vector>

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to draw an image onto the screen.
	// --------------------------------------------------
	class Image
	{
	private: 
		Tmpl8::Surface* m_Source = nullptr;
		int m_X = 0;
		int m_Y = 0;
		int short m_XFrames = 0;
		int short m_YFrames = 0;
		int short m_CurrentXFrame = 0;
		int short m_CurrentYFrame = 0;
		int m_Width = 0;
		int m_Height = 0;

	public:
		Image(char* sourcePath, int x, int y, short xFrames = 1, short yFrames = 1);
		void DrawImage(Tmpl8::Surface* screen);
		int GetOpacityValueFromPixelInSourceImage(int xPosition, int yPosition);
		int GetColourValueFromPixelInSourceImage(int xPosition, int yPosition);
		void SetPosition(int x, int y);
		void SetCurrentXFrame(int currentXFrame);
		void SetCurrentYFrame(int currentYFrame);
		std::vector<int> GetPosition();
		int GetWidth();
		int GetHeight();
		~Image();
	};
}