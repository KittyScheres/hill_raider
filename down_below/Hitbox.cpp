#include "Hitbox.h"

namespace DownBelow
{
	Hitbox::Hitbox(int x, int y, int width, int Height)
	{
		halfWidth = width / 2;
		halfHeight = Height / 2;
		xPos = x;
		yPos = y;
	}

	void Hitbox::SetPosition(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

	void Hitbox::SetWidth(int width)
	{
		halfWidth = width / 2;
	}

	void Hitbox::SetHeight(int height)
	{
		halfHeight = height / 2;
	}

	float Hitbox::GetHalfDiameter()
	{
		return sqrtf((halfWidth * halfWidth) + (halfHeight * halfHeight));;
	}

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


	void Hitbox::RenderHitbox(Tmpl8::Surface* screen){
		int startXPos = xPos - halfWidth;
		int startYPos = yPos - halfHeight;

		for (int y = 0; y < (halfHeight * 2); y++) {
			if (startYPos + y < screen->GetHeight()) {
				for (int x = 0; x < (halfWidth * 2); x++) {
					if (startXPos + x < screen->GetWidth()) {
						screen->GetBuffer()[(startXPos + x) + ((startYPos + y) * screen->GetWidth())] = debugColour;
					}
				}
			}
		}
	}
}