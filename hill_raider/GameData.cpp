#include "gameData.h"

namespace HillRaider
{
	GameData* GameData::s_Instance = nullptr;

	// --------------------------------------------------
	// This method returns the singelton instance of
	// the game data class.
	// --------------------------------------------------
	GameData* GameData::GetInstance()
	{
		if (s_Instance == nullptr) {
			s_Instance = new GameData();
		}
		return s_Instance;
	}

	// --------------------------------------------------
	// This method destroys the singleton instance of 
	// the game data class.
	// --------------------------------------------------
	void GameData::DestroyInstance()
	{
		if (s_Instance != nullptr) {
			delete s_Instance;
			s_Instance = nullptr;
		}
	}
}