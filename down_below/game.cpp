#include "game.h"
#include "SDL.h"
#include "surface.h"
#include "StartMenu.h"
#include <random>
#include <time.h>

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		SetState(new HillRaider::StartMenu(this));
		inputManager = HillRaider::InputManager::GetInstance();
		srand(time(NULL));
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		if (currentState != nullptr) {
			delete currentState;
			currentState = nullptr;
		}

		inputManager->DestroyInstance();
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// check if application hasn't been paused
		if (deltaTime < 100.f) {
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
	}

	// -----------------------------------------------------------
	// Set the current state of the game
	// -----------------------------------------------------------
	void Game::SetState(HillRaider::State* newState) {
		delete currentState;
		currentState = newState;
	}

	// -----------------------------------------------------------
	// Close the game
	// -----------------------------------------------------------
	void Game::CloseGame() {
		SDL_Event closeWindowEvent;
		closeWindowEvent.type = SDL_QUIT;
		SDL_PushEvent(&closeWindowEvent);
	}
};