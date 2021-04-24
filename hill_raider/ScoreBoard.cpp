#include "ScoreBoard.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the score
	// board.
	// --------------------------------------------------
	ScoreBoard::ScoreBoard(int x, int y)
	{
		m_Source = new Image("assets/text/number_line.png", 0, 0, 10);
		m_X = x;
		m_Y = y;
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
				m_Source->SetPosition(m_X + (i * GetWidthOfChar()), m_Y);
				m_Source->SetCurrentXFrame(number);
				m_Source->DrawImage(screen);
			}
		}
	}

	// --------------------------------------------------
	// This mehtod is used to set the position for the score
	// board.
	// --------------------------------------------------
	void ScoreBoard::SetPosition(int x, int y)
	{
		m_X = x;
		m_Y = y;
	}

	// --------------------------------------------------
	// This method is used to get the position of the score
	// board.
	// --------------------------------------------------
	std::vector<int> ScoreBoard::GetPosition()
	{
		return std::vector<int>{ m_X, m_Y };
	}

	// --------------------------------------------------
	// This method is used to get the width of 1 number on
	// on the score board.
	// --------------------------------------------------
	int ScoreBoard::GetWidthOfChar()
	{
		return m_Source->GetWidth();
	}

	// --------------------------------------------------
	// This method is used to get the height a 1 char on 
	// the score board.
	// --------------------------------------------------
	int ScoreBoard::GetHeightOfChar()
	{
		return m_Source->GetHeight();
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// score board image source.
	// --------------------------------------------------
	ScoreBoard::~ScoreBoard()
	{
		if (m_Source != nullptr) {
			delete m_Source;
			m_Source = nullptr;
		}
	}
}