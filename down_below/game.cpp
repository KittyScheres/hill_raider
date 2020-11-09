#include "game.h"
#include "surface.h"
#include "StartMenu.h"
#include <cstdio> //printf

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		SetState(new DownBelow::StartMenu());
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete currentState;
		currentState = nullptr;
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);
		// call update the game
		currentState->Update(deltaTime);
		// check and apply collision
		currentState->LateUpdate();
		// draw objects
		currentState->Render(screen);
	}

	// -----------------------------------------------------------
	// Set the current state of the game
	// -----------------------------------------------------------
	void Game::SetState(DownBelow::State* newState) {
		delete currentState;
		currentState = newState;
	}
};