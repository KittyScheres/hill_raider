#include "Image.h"

namespace DownBelow
{
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	Image::Image(char* srcPath, int iX, int iY)
	{
		src = new Tmpl8::Surface(srcPath);
		x = iX;
		y = iY;
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Image::DrawImage(Tmpl8::Surface* screen)
	{
		int screenWidth = screen->GetWidth();
		int srcWidth = src->GetWidth();

		for (int iY = 0; iY < src->GetHeight(); iY++) {
			int screenYPos = y + iY;
			if (screenYPos >= 0 && screenYPos <= screen->GetHeight()) {
				for (int iX = 0; iX < srcWidth; iX++) {
					int screenXpos = x + iX;
					if (screenXpos >= 0 && screenXpos <= screenWidth) {
						if ((src->GetBuffer()[iX + (iY * srcWidth)] >> 24) != 0) {
							screen->GetBuffer()[screenXpos + (screenYPos * screenWidth)] = src->GetBuffer()[iX + (iY * srcWidth)];
						}
					}
				}
			}
		}
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Image::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	int* Image::GetPosition()
	{
		int position[2]{ x, y };
		return position;
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	int Image::GetWidth()
	{
		return src->GetWidth();
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	int Image::GetHeight()
	{
		return src->GetHeight();
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	Image::~Image()
	{
		if (src != nullptr) {
			delete src;
			src = nullptr;
		}
	}
}