#include "Image.h"

namespace HillRaider
{
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	Image::Image(char* srcPath, int iX, int iY, short iXFrames, short iYFrames)
	{
		src = new Tmpl8::Surface(srcPath);
		x = iX;
		y = iY;
		xFrames = iXFrames;
		yFrames = iYFrames;
		width = src->GetWidth() / iXFrames;
		height = src->GetHeight() / iYFrames;
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Image::DrawImage(Tmpl8::Surface* screen)
	{
		int screenWidth = screen->GetWidth();

		for (int iY = 0; iY < height; iY++) {
			int screenYPos = y + iY;
			if (screenYPos >= 0 && screenYPos <= screen->GetHeight()) {
				for (int iX = 0; iX < width; iX++) {
					int screenXpos = x + iX;
					if (screenXpos >= 0 && screenXpos <= screenWidth) {
						if ((src->GetBuffer()[(iX + (currentXFrame * width)) + ((iY + (currentYFrame * height)) * src->GetWidth())] >> 24) != 0) {
							screen->GetBuffer()[screenXpos + (screenYPos * screenWidth)] = src->GetBuffer()[(iX + (currentXFrame * width)) + ((iY + (currentYFrame * height)) * src->GetWidth())];
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
	void Image::SetCurrentXFrame(int iCurrentXFrame)
	{
		if (iCurrentXFrame < xFrames && iCurrentXFrame >= 0) {
			currentXFrame = iCurrentXFrame;
		}
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void Image::SetCurrentYFrame(int iCurrentYFrame)
	{
		if (iCurrentYFrame < yFrames && iCurrentYFrame >= 0) {
			currentYFrame = iCurrentYFrame;
		}
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
		return width;
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	int Image::GetHeight()
	{
		return height;
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