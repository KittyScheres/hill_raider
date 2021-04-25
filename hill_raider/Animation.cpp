#include "animation.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the animation.
	// --------------------------------------------------
	Animation::Animation(char* sourcePath, short xFrames, short yFrames, float timePerFrame, int x, int y, bool loop)
	{
		m_Source = new Image(sourcePath, x, y, xFrames, yFrames);
		m_XFrames = xFrames;
		m_TimePerFrame = timePerFrame;
		m_Loop = loop;
	}

	// --------------------------------------------------
	// This method is used to update the animation.
	// --------------------------------------------------
	void Animation::UpdateAnimation(float deltaTime)
	{
		if (m_AnimationTimer >= m_TimePerFrame) {
			if (m_CurrentXFrame < m_XFrames) {
				m_Source->SetCurrentXFrame(++m_CurrentXFrame);
				m_AnimationTimer = 0.f;
			}
			else if (m_Loop) {
				m_Source->SetCurrentXFrame(0);
				m_CurrentXFrame = 0;
				m_AnimationTimer = 0.f;
			}
		}
		else {
			m_AnimationTimer += deltaTime;
		}
	}

	// --------------------------------------------------
	// This method is used to the animation on to the 
	// screen.
	// --------------------------------------------------
	void Animation::DrawAnimation(Tmpl8::Surface* screen)
	{
		m_Source->DrawImage(screen);
	}

	// --------------------------------------------------
	// This method is used to set the position of the 
	// animation.
	// --------------------------------------------------
	void Animation::SetPosition(int x, int y)
	{
		m_Source->SetPosition(x, y);
	}

	// --------------------------------------------------
	// This method is used to set the time per frame for
	// the animation.
	// --------------------------------------------------
	void Animation::SetTimePerFrame(float timePerFrame)
	{
		m_TimePerFrame = timePerFrame;
	}

	// --------------------------------------------------
	// This method is used to update the current x axis
	// of the sampel frame from the animation source.
	// --------------------------------------------------
	void Animation::SetCurrentXFrame(short currentXFrame)
	{
		m_CurrentXFrame = currentXFrame;
		m_Source->SetCurrentXFrame(currentXFrame);
	}

	// --------------------------------------------------
	// This method is used to update the current y axis
	// of the sampel frame from the animation source.
	// --------------------------------------------------
	void Animation::SetCurrentYFrame(short currentYFrame)
	{
		m_Source->SetCurrentYFrame(currentYFrame);
	}

	// --------------------------------------------------
	// This method is used to get the current position
	// the animation.
	// --------------------------------------------------
	std::vector<int> Animation::GetPosition()
	{
		return m_Source->GetPosition();
	}

	// --------------------------------------------------
	// This method is used to get the display width of
	// the animation.
	// --------------------------------------------------
	int Animation::GetWidth()
	{
		return m_Source->GetWidth();
	}

	// --------------------------------------------------
	// This method is used to get the display height of
	// the animation.
	// --------------------------------------------------
	int Animation::GetHeight()
	{
		return m_Source->GetHeight();
	}

	// --------------------------------------------------
	// This deconstructor is used to safly free up the
	// memory of the animation source.
	// --------------------------------------------------
	Animation::~Animation()
	{
		if (m_Source != nullptr) {
			delete m_Source;
			m_Source = nullptr;
		}
	}
}