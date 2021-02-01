#include "Credits.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	Credits::Credits(GameCallback* iCallback)
	{
		callback = iCallback;
		
		background = new Image("assets/ui/background.png", 0, 0);
	}
	
	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	void Credits::Update(float deltaTime)
	{
		if (InputManager::GetInstance()->KeyPressed(InputManager::Keys::ESCAPE)) {
			callback->SetNextState(new StartMenu(callback));
		}
	}
	
	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	void Credits::Render(Tmpl8::Surface* screen)
	{
		background->DrawImage(screen);
	}
	
	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	Credits::~Credits()
	{
		if (background != nullptr) {
			delete background;
			background = nullptr;
		}

		callback = nullptr;
	}
}