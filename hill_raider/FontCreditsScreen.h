#pragma once

#include "Image.h"

namespace HillRaider
{
	// ------------------------------------------------------------
	// 
	// ------------------------------------------------------------
	class FontCreditsScreen
	{
	private:
		Image* screenTitle = nullptr;
		Image* fontCredits = nullptr;

	public:
		FontCreditsScreen();
		void Render(Tmpl8::Surface* screen);
		~FontCreditsScreen();
	};
}