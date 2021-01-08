#include "Hitbox.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Hitbox::Hitbox(int x, int y, int width, int Height)
	{
		halfWidth = width / 2;
		halfHeight = Height / 2;
		xPos = x;
		yPos = y;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Hitbox::SetPosition(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Hitbox::SetWidth(int width)
	{
		halfWidth = width / 2;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Hitbox::SetHeight(int height)
	{
		halfHeight = height / 2;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	std::vector<int> Hitbox::GetPosition() {
		return std::vector<int>{xPos, yPos};
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int Hitbox::GetHalfWidth()
	{
		return halfWidth;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int Hitbox::GetHalfHeight()
	{
		return halfHeight;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	float Hitbox::GetHalfDiameter()
	{
		return sqrtf((halfWidth * halfWidth) + (halfHeight * halfHeight));;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	std::vector<std::vector<int>> Hitbox::GetBoxPoints()
	{
		std::vector<std::vector<int>> boxPoints;

		for (int y = 0; y < 2; y++) {
			for (int x = 0; x < 2; x++){
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
	//
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