#pragma once

#include "Image.h"
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
		Image* src = nullptr;
		int x = 0;
		int y = 0;

	public:
		ScoreBoard(int iX = 0, int iY = 0);
		void DrawScore(std::string score, Tmpl8::Surface* screen);
		void SetPosition(int iX, int iY);
		std::vector<int> GetPosition();
		int GetCharWidth();
		int GetCharHeight();
		~ScoreBoard();
	};
}

