#pragma once

#include "Image.h"
#include "GameData.h"

namespace HillRaider
{
	class Ui
	{
	private:
		Image* healthBar[GameData::MAX_HEALTH];
	public:
		Ui();
		void Render(Tmpl8::Surface* screen);
		~Ui();
	};
}