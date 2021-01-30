#include "Hitbox.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties
	// for a hitbox.
	// --------------------------------------------------
	Hitbox::Hitbox(int x, int y, int width, int Height)
	{
		halfWidth = width / 2;
		halfHeight = Height / 2;
		xPos = x;
		yPos = y;
	}

	// --------------------------------------------------
	// This method is used to set the position of a hitbox.
	// --------------------------------------------------
	void Hitbox::SetPosition(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

	// --------------------------------------------------
	// This method is used to set the width of a hitbox.
	// --------------------------------------------------
	void Hitbox::SetWidth(int width)
	{
		halfWidth = width / 2;
	}

	// --------------------------------------------------
	// This method is used to set the height of a hitbox.
	// --------------------------------------------------
	void Hitbox::SetHeight(int height)
	{
		halfHeight = height / 2;
	}

	// --------------------------------------------------
	// This method is used to get the position of a
	// hitbox.
	// --------------------------------------------------
	std::vector<int> Hitbox::GetPosition() {
		return std::vector<int>{xPos, yPos};
	}

	// --------------------------------------------------
	// This method is used to get half of the width of
	// a hitbox.
	// --------------------------------------------------
	int Hitbox::GetHalfWidth()
	{
		return halfWidth;
	}

	// --------------------------------------------------
	// This method is used to get half of the height of
	// a hitbox. 
	// --------------------------------------------------
	int Hitbox::GetHalfHeight()
	{
		return halfHeight;
	}

	// --------------------------------------------------
	// This method is used to get the radius of a circel
	// drawn around a hitbox.
	// --------------------------------------------------
	float Hitbox::GetCircleRadius()
	{
		return sqrtf((float)(halfWidth * halfWidth) + (float)(halfHeight * halfHeight));
	}

	// --------------------------------------------------
	// This method is used to get the position of all 4
	// corners of a hitbox.
	// --------------------------------------------------
	std::vector<std::vector<int>> Hitbox::GetBoxPoints()
	{
		std::vector<std::vector<int>> boxPoints;

		for (short y = 0; y < 2; y++) {
			for (short x = 0; x < 2; x++){
				std::vector<int> point;
				
				switch (x)
				{
				case 0:
					point.push_back(xPos - halfWidth);
					break;

				case 1:
					point.push_back(xPos + halfWidth);
					break;
				}

				switch (y)
				{
				case 0:
					point.push_back(yPos - halfHeight);
					break;

				case 1:
					point.push_back(yPos + halfHeight);
					break;
				}

				boxPoints.push_back(point);
			}
		}

		return boxPoints;
	}

	// --------------------------------------------------
	// This method is used to draw a hitbox on to the
	// screen. This mehtod will only be used for debug
	// purposes.
	// --------------------------------------------------
	void Hitbox::RenderHitbox(Tmpl8::Surface* screen){
		int startXPos = xPos - halfWidth;
		int startYPos = yPos - halfHeight;

		for (int y = 0; y < (halfHeight * 2); y++) {
			if (startYPos + y < screen->GetHeight() && startYPos + y >= 0) {
				for (int x = 0; x < (halfWidth * 2); x++) {
					if (startXPos + x < screen->GetWidth() && startXPos + x >= 0) {
						screen->GetBuffer()[(startXPos + x) + ((startYPos + y) * screen->GetWidth())] = debugColour;
					}
				}
			}
		}
	}
}