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
		SetState(new DownBelow::StartMenu(this));
		inputManager = DownBelow::InputManager::GetInstance();
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete currentState;
		currentState = nullptr;

		inputManager->DestroyInstance();
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);
		// get new key inputs
		inputManager->UpdateKeysState();
		// call update for the game
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