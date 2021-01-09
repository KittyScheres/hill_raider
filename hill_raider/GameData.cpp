#include "GameData.h"

namespace HillRaider
{
	GameData* GameData::instance = nullptr;

	// --------------------------------------------------
	// This method returns the singelton instance of
	// the game data class.
	// --------------------------------------------------
	GameData* GameData::GetInstance()
	{
		if (instance == nullptr) {
			instance = new GameData();
		}
		return instance;
	}

	// --------------------------------------------------
	// This method destroys the singleton instance of 
	// the game data class.
	// --------------------------------------------------
	void GameData::DestroyInstance()
	{
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}
}