#pragma once

#include "surface.h"
#include <vector>

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to draw an image on to the screen.
	// --------------------------------------------------
	class Image
	{
	private: 
		Tmpl8::Surface* src = nullptr;
		int x = 0;
		int y = 0;
		int short xFrames = 0;
		int short yFrames = 0;
		int short currentXFrame = 0;
		int short currentYFrame = 0;
		int width = 0;
		int height = 0;

	public:
		Image(char* srcPath, int iX, int iY, short iXFrames = 1, short iYFrames = 1);
		void DrawImage(Tmpl8::Surface* screen);
		void SetPosition(int iX, int iY);
		void SetCurrentXFrame(int iCurrentXFrame);
		void SetCurrentYFrame(int iCurrentYFrame);
		std::vector<int> GetPosition();
		int GetWidth();
		int GetHeight();
		~Image();
	};
}