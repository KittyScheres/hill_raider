#pragma once

namespace HillRaider
{
	// --------------------------------------------------
	// This class contains global variables for the game.
	// --------------------------------------------------
	class GameData
	{
	private:
		static GameData* instance;

	public:
		const static short MAX_HEALTH = 6;
		const static int MAX_POINTS = 99999;
		const static short POINTS_FOR_HEALTH = 20;
		short playerHealth = 6;
		int playerPoints = 0;

	public:
		static GameData* GetInstance();
		static void DestroyInstance();

	private:
		GameData() {};
		~GameData() {};
	};
}