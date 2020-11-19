#include "GameData.h"

namespace DownBelow
{
	GameData* GameData::instance = nullptr;

	// --------------------------------------------------
	//
	// --------------------------------------------------
	GameData* GameData::GetInstance()
	{
		if (instance == nullptr) {
			instance = new GameData();
		}
		return instance;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GameData::DestroyInstance()
	{
		delete instance;
		instance = nullptr;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	GameData::GameData() {}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	GameData::~GameData() {}
}