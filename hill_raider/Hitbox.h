#pragma once

#include <vector>
#include <math.h>
#include "surface.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to setup and keep track of a
	// which can be used to process entity on entity
	// collision.
	// --------------------------------------------------
	class Hitbox
	{
	private:
		int m_X = 0;
		int m_Y = 0;
		int m_HalfWidth = 0;
		int m_HalfHeight = 0;

	public:
		Hitbox(int x, int y, int width, int Height);
		void SetPosition(int x, int y);
		void SetWidth(int width);
		void SetHeight(int height);
		std::vector<int> GetPosition();
		int GetHalfWidth();
		int GetHalfHeight();
		float GetCircleRadius();
		std::vector<std::vector<int>> GetBoxPoints();
	};
}