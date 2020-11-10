#include "StartMenu.h"
#include <cstdio> //printf

namespace DownBelow 
{
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	StartMenu::StartMenu(StateCallback* iCallback)
	{
		callback = iCallback;
		tank = new Animation("assets/ctankbase.tga", 16, 50.f, true, 0, 0);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void StartMenu::Update(float deltaTime)
	{
		tank->UpdateAnimation(deltaTime);
		timer += deltaTime;

		if (timer >= 6000) {
			callback->SetState(new StartMenu(callback));
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void StartMenu::Render(Tmpl8::Surface* screen)
	{
		tank->DrawAnimation(screen);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	StartMenu::~StartMenu()
	{
		delete tank;
		tank = nullptr;
		callback = nullptr;
	}
}