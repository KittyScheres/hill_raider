#include "image.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the image.
	// --------------------------------------------------
	Image::Image(char* sourcePath, int x, int y, short xFrames, short yFrames)
	{
		m_Source = new Tmpl8::Surface(sourcePath);
		m_X = x;
		m_Y = y;
		m_XFrames = xFrames;
		m_YFrames = yFrames;
		m_Width = m_Source->GetWidth() / xFrames;
		m_Height = m_Source->GetHeight() / yFrames;
	}

	// --------------------------------------------------
	// This method is used to draw the image onto the 
	// screen.
	// --------------------------------------------------
	void Image::DrawImage(Tmpl8::Surface* screen)
	{
		int screenWidth = screen->GetWidth();

		for (int y = 0; y < m_Height; y++) {
			int screenYPos = m_Y + y;
			if (screenYPos >= 0 && screenYPos <= screen->GetHeight()) {
				for (int x = 0; x < m_Width; x++) {
					int screenXpos = m_X + x;
					if (screenXpos >= 0 && screenXpos <= screenWidth) {
						if (GetOpacityValueFromPixelInSourceImage(x, y) != 0) {
							screen->GetBuffer()[screenXpos + (screenYPos * screenWidth)] = GetColourValueFromPixelInSourceImage(x, y);
						}
					}
				}
			}
		}
	}

	// --------------------------------------------------
	// This method is used to get the opacity value of a
	// pixel in the source image.
	// --------------------------------------------------
	int Image::GetOpacityValueFromPixelInSourceImage(int xPosition, int yPosition) {
		return GetColourValueFromPixelInSourceImage(xPosition, yPosition) >> 24;
	}

	// --------------------------------------------------
	// This method is used to get the colour value of a
	// pixel in the source image.
	// --------------------------------------------------
	int Image::GetColourValueFromPixelInSourceImage(int xPosition, int yPosition) {
		return m_Source->GetBuffer()[(xPosition + (m_CurrentXFrame * m_Width)) + ((yPosition + (m_CurrentYFrame * m_Height)) * m_Source->GetWidth())];
	}

	// --------------------------------------------------
	// This method is used to change the position of the 
	// image.
	// --------------------------------------------------
	void Image::SetPosition(int x, int y)
	{
		m_X = x;
		m_Y = y;
	}

	// --------------------------------------------------
	// This method is used to update the current x axis
	// of the sample frame from the image source.
	// --------------------------------------------------
	void Image::SetCurrentXFrame(int currentXFrame)
	{
		if (currentXFrame < m_XFrames && currentXFrame >= 0) {
			m_CurrentXFrame = currentXFrame;
		}
	}

	// --------------------------------------------------
	// This method is used to update the current y axis
	// of the sample frame from the image source.
	// --------------------------------------------------
	void Image::SetCurrentYFrame(int currentYFrame)
	{
		if (currentYFrame < m_YFrames && currentYFrame >= 0) {
			m_CurrentYFrame = currentYFrame;
		}
	}

	// --------------------------------------------------
	// This method is used to get the current position of
	// the image.
	// --------------------------------------------------
	std::vector<int> Image::GetPosition()
	{
		return std::vector<int>{ m_X, m_Y };
	}

	// --------------------------------------------------
	// This method is used to get the display width of
	// the image.
	// --------------------------------------------------
	int Image::GetWidth()
	{
		return m_Width;
	}

	// --------------------------------------------------
	// This method is used to get the display height of
	// the image.
	// --------------------------------------------------
	int Image::GetHeight()
	{
		return m_Height;
	}

	// --------------------------------------------------
	// This deconstructor is used to safely free up the
	// memory of the image source.
	// --------------------------------------------------
	Image::~Image()
	{
		if (m_Source != nullptr) {
			delete m_Source;
			m_Source = nullptr;
		}
	}
}