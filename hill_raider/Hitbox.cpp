#include "Hitbox.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties
	// for a hitbox.
	// --------------------------------------------------
	Hitbox::Hitbox(int x, int y, int width, int Height)
	{
		m_HalfWidth = width / 2;
		m_HalfHeight = Height / 2;
		m_X = x;
		m_Y = y;
	}

	// --------------------------------------------------
	// This method is used to set the position of a hitbox.
	// --------------------------------------------------
	void Hitbox::SetPosition(int x, int y)
	{
		m_X = x;
		m_Y = y;
	}

	// --------------------------------------------------
	// This method is used to set the width of a hitbox.
	// --------------------------------------------------
	void Hitbox::SetWidth(int width)
	{
		m_HalfWidth = width / 2;
	}

	// --------------------------------------------------
	// This method is used to set the height of a hitbox.
	// --------------------------------------------------
	void Hitbox::SetHeight(int height)
	{
		m_HalfHeight = height / 2;
	}

	// --------------------------------------------------
	// This method is used to get the position of a
	// hitbox.
	// --------------------------------------------------
	std::vector<int> Hitbox::GetPosition() {
		return std::vector<int>{m_X, m_Y};
	}

	// --------------------------------------------------
	// This method is used to get half of the width of
	// a hitbox.
	// --------------------------------------------------
	int Hitbox::GetHalfWidth()
	{
		return m_HalfWidth;
	}

	// --------------------------------------------------
	// This method is used to get half of the height of
	// a hitbox. 
	// --------------------------------------------------
	int Hitbox::GetHalfHeight()
	{
		return m_HalfHeight;
	}

	// --------------------------------------------------
	// This method is used to get the radius of a circel
	// drawn around a hitbox.
	// --------------------------------------------------
	float Hitbox::GetCircleRadius()
	{
		return sqrtf((float)(m_HalfWidth * m_HalfWidth) + (float)(m_HalfHeight * m_HalfHeight));
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
					point.push_back(m_X - m_HalfWidth);
					break;

				case 1:
					point.push_back(m_X + m_HalfWidth);
					break;
				}

				switch (y)
				{
				case 0:
					point.push_back(m_Y - m_HalfHeight);
					break;

				case 1:
					point.push_back(m_Y + m_HalfHeight);
					break;
				}

				boxPoints.push_back(point);
			}
		}

		return boxPoints;
	}
}