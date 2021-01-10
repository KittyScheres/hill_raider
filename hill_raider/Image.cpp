#include "Image.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the image.
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
	// This method is used to draw the image on to the 
	// screen.
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
	// This method is used to change the position of the 
	// image.
	// --------------------------------------------------
	void Image::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
	}

	// --------------------------------------------------
	// This method is used to update the current x axis
	// of the sampel frame from the image source.
	// --------------------------------------------------
	void Image::SetCurrentXFrame(int iCurrentXFrame)
	{
		if (iCurrentXFrame < xFrames && iCurrentXFrame >= 0) {
			currentXFrame = iCurrentXFrame;
		}
	}

	// --------------------------------------------------
	// This method is used to update the current y axis
	// of the sampel frame from the image source.
	// --------------------------------------------------
	void Image::SetCurrentYFrame(int iCurrentYFrame)
	{
		if (iCurrentYFrame < yFrames && iCurrentYFrame >= 0) {
			currentYFrame = iCurrentYFrame;
		}
	}

	// --------------------------------------------------
	// This method is used to get the current position of
	// the image.
	// --------------------------------------------------
	int* Image::GetPosition()
	{
		int position[2]{ x, y };
		return position;
	}

	// --------------------------------------------------
	// This method is used to get the display width of
	// the image.
	// --------------------------------------------------
	int Image::GetWidth()
	{
		return width;
	}

	// --------------------------------------------------
	// This method is used to get the display height of
	// the image.
	// --------------------------------------------------
	int Image::GetHeight()
	{
		return height;
	}

	// --------------------------------------------------
	// This deconstructor is used to safly free up the
	// memory of the image source.
	// --------------------------------------------------
	Image::~Image()
	{
		if (src != nullptr) {
			delete src;
			src = nullptr;
		}
	}
}