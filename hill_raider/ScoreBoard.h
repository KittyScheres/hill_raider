#pragma once

#include "image.h"
#include <string>

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to draw a dynamic score board
	// on to the screen.
	// --------------------------------------------------
	class ScoreBoard
	{
	private:
		Image* m_Source = nullptr;
		int m_X = 0;
		int m_Y = 0;

	public:
		ScoreBoard(int x = 0, int y = 0);
		void DrawScore(std::string score, Tmpl8::Surface* screen);
		void SetPosition(int x, int y);
		std::vector<int> GetPosition();
		int GetWidthOfChar();
		int GetHeightOfChar();
		~ScoreBoard();
	};
}

