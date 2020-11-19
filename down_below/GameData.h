#pragma once

namespace DownBelow
{
	class GameData
	{
	private:
		static GameData* instance;

	public:
		const short MAX_HEALTH = 6;
		short playerHealth = 6;

	public:
		static GameData* GetInstance();
		static void DestroyInstance();

	private:
		GameData();
		~GameData();
	};
}