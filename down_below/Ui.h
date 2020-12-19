#pragma once

#include "Image.h"
#include "GameData.h"

namespace HillRaider
{
	class Ui
	{
	private:
		Image* healthBar[GameData::MAX_HEALTH];
		GameData* gameData = nullptr;
	public:
		Ui();
		void Render(Tmpl8::Surface* screen);
		~Ui();
	};
}