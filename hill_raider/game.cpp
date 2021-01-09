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
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//ShowWindow(GetConsoleWindow(), SW_HIDE);
		currentState = new HillRaider::StartMenu(this);
		inputManager = HillRaider::InputManager::GetInstance();
		srand(time(NULL));
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		if (screen != nullptr) {
			delete screen;
			screen = nullptr;
		}

		if (nextState != nullptr) {
			delete nextState;
			nextState = nullptr;
		}

		if (currentState != nullptr) {
			delete currentState;
			currentState = nullptr;
		}

		inputManager->DestroyInstance();

		delete this;
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		if (deltaTime < 100.f) {
			screen->Clear(0);
			inputManager->UpdateKeysState();
			currentState->Update(deltaTime);
			currentState->LateUpdate();
			currentState->Render(screen);
			SetState();
		}
	}

	// -----------------------------------------------------------
	// Set the current state of the game
	// -----------------------------------------------------------
	void Game::SetState()
	{
		if (nextState != nullptr) {
			delete currentState;
			currentState = nextState;
			nextState = nullptr;
			currentState->SetupSingletons();
		}
	}

	// -----------------------------------------------------------
	// Set the next state of the game
	// -----------------------------------------------------------
	void Game::SetNextState(HillRaider::State* newState) {
		nextState = newState;
	}

	// -----------------------------------------------------------
	// End the application
	// -----------------------------------------------------------
	void Game::CloseGame() {
		SDL_Event closeWindowEvent;
		closeWindowEvent.type = SDL_QUIT;
		SDL_PushEvent(&closeWindowEvent);
	}
};