#include "StartMenu.h"
#include <cstdio> //printf

namespace DownBelow 
{
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	StartMenu::StartMenu()
	{
		tank = new Animation("assets/ctankbase.tga", 16, 50.f, true, 0, 0);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void StartMenu::Update(float deltaTime)
	{
		tank->UpdateAnimation(deltaTime);
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
	StartMenu::~StartMenu() {
		delete tank;
		tank = nullptr;
	}
}