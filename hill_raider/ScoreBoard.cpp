#include "ScoreBoard.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the score
	// board.
	// --------------------------------------------------
	ScoreBoard::ScoreBoard(int iX, int iY)
	{
		src = new Image("assets/text/number_line.png", 0, 0, 10);
		x = iX;
		y = iY;
	}

	// --------------------------------------------------
	// This mehod is used to draw a score on to the screen.
	// --------------------------------------------------
	void ScoreBoard::DrawScore(std::string score, Tmpl8::Surface* screen)
	{
		int scoreSize = score.size();
		
		for (int i = 0; i < scoreSize; i++) {
			short number = ((int)score[i]) - ((int)'0');

			if (number >= 0 && number <= 9) {
				src->SetPosition(x + (i * GetCharWidth()), y);
				src->SetCurrentXFrame(number);
				src->DrawImage(screen);
			}
		}
	}

	// --------------------------------------------------
	// This mehtod is used to set the position for the score
	// board.
	// --------------------------------------------------
	void ScoreBoard::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
	}

	// --------------------------------------------------
	// This method is used to get the position of the score
	// board.
	// --------------------------------------------------
	std::vector<int> ScoreBoard::GetPosition()
	{
		return std::vector<int>{ x, y };
	}

	// --------------------------------------------------
	// This method is used to get the width of 1 number on
	// on the score board.
	// --------------------------------------------------
	int ScoreBoard::GetCharWidth()
	{
		return src->GetWidth();
	}

	// --------------------------------------------------
	// This method is used to get the height a 1 char on 
	// the score board.
	// --------------------------------------------------
	int ScoreBoard::GetCharHeight()
	{
		return src->GetHeight();
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// score board image source.
	// --------------------------------------------------
	ScoreBoard::~ScoreBoard()
	{
		if (src != nullptr) {
			delete src;
			src = nullptr;
		}
	}
}