#pragma once

#include <vector>
#include <math.h>
#include "surface.h"

namespace DownBelow
{
	class Hitbox
	{
	private:
		int xPos = 0;
		int yPos = 0;
		int halfWidth = 0;
		int halfHeight = 0;
		int debugColour = 127 << 16;

	public:
		Hitbox(int x, int y, int width, int Height);
		void SetPosition(int x, int y);
		void SetWidth(int width);
		void SetHeight(int height);
		std::vector<int> GetPosition();
		float GetHalfDiameter();
		std::vector<std::vector<int>> GetBoxPoints();
		void RenderHitbox(Tmpl8::Surface* screen);
	};
}