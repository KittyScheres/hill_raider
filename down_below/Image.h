#pragma once

#include "surface.h"

namespace HillRaider
{
	class Image
	{
	private: 
		Tmpl8::Surface* src = nullptr;
		int x = 0;
		int y = 0;

	public:
		Image(char* srcPath, int iX, int iY);
		void DrawImage(Tmpl8::Surface* screen);
		void SetPosition(int iX, int iY);
		int* GetPosition();
		int GetWidth();
		int GetHeight();
		~Image();
	};
}