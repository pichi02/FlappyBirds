#pragma once
#include"raylib.h"
namespace app
{
	namespace menu
	{
		void InitMenu();
		void UpdateMenu();
		void DrawMenu();
		void UnloadMenu();
		extern bool isMultiplayer;
		
	}
}