#pragma once

#include <vector>
#include <math.h>

namespace DownBelow
{
	class Hitbox
	{
	private:
		int xPos = 0;
		int yPos = 0;
		int halfWidth = 0;
		int halfHeight = 0;

	public:
		Hitbox(int x, int y, int width, int Height);
		void SetPosition(int x, int y);
		void SetWidth(int width);
		void SetHeight(int height);
		float GetHalfDiameter();
		std::vector<std::vector<int>> GetBoxPoints();
	};
}