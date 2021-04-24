#pragma once

namespace HillRaider
{
	// --------------------------------------------------
	// This class contains global variables for the game.
	// --------------------------------------------------
	class GameData
	{
	private:
		static GameData* s_Instance;

	public:
		const static short c_s_MaxHealth = 6;
		const static int c_s_MaxPoints = 99999;
		const static short c_s_PointsForHealth = 20;
		short m_PlayerHealth = 6;
		int m_PlayerPoints = 0;

	public:
		static GameData* GetInstance();
		static void DestroyInstance();

	private:
		GameData() {};
		~GameData() {};
	};
}