#include "game.h"
#include "SDL.h"
#include "surface.h"
#include "startMenu.h"
#include <random>
#include <time.h>

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application.
	// -----------------------------------------------------------
	void Game::Init()
	{
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		m_CurrentState = new HillRaider::StartMenu(this);
		m_InputManager = HillRaider::InputManager::GetInstance();
		srand((int)time(NULL));
	}
	
	// -----------------------------------------------------------
	// Close down the application.
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		if (m_Screen != nullptr) {
			delete m_Screen;
			m_Screen = nullptr;
		}

		if (m_NextState != nullptr) {
			delete m_NextState;
			m_NextState = nullptr;
		}

		if (m_CurrentState != nullptr) {
			delete m_CurrentState;
			m_CurrentState = nullptr;
		}

		m_InputManager->DestroyInstance();

		delete this;
	}

	// -----------------------------------------------------------
	// Main application tick function.
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// Is the delta time to high?
		if (deltaTime < 100.f) {
			m_Screen->Clear(0);
			m_InputManager->UpdateKeysState();
			m_CurrentState->Update(deltaTime);
			m_CurrentState->LateUpdate();
			m_CurrentState->Render(m_Screen);
			SetState();
		}
	}

	// -----------------------------------------------------------
	// Set the current state of the game.
	// -----------------------------------------------------------
	void Game::SetState()
	{
		if (m_NextState != nullptr) {
			delete m_CurrentState;
			m_CurrentState = m_NextState;
			m_NextState = nullptr;
			m_CurrentState->SetupSingletons();
		}
	}

	// -----------------------------------------------------------
	// Set the next state of the game.
	// -----------------------------------------------------------
	void Game::SetNextState(HillRaider::State* newState) {
		m_NextState = newState;
	}

	// -----------------------------------------------------------
	// End the application.
	// -----------------------------------------------------------
	void Game::CloseGame() {
		SDL_Event closeWindowEvent;
		closeWindowEvent.type = SDL_QUIT;
		SDL_PushEvent(&closeWindowEvent);
	}
};