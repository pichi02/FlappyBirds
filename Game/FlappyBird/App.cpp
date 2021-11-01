#include "App.h"
#include "raylib.h"

#include "Menu.h"
#include "Credits.h"
#include "Gameplay.h"
#include "Pause.h"
#include "GameOver.h"
#include "Player.h"
#include "Obstacle.h"

using namespace app;
using namespace menu;
using namespace credits;
using namespace gameplay;
using namespace pause;
using namespace gameover;
using namespace player;
using namespace obstacle;

namespace app
{
	static int screenWidth = 800;
	static int screenHeight = 600;
	Music music;

	bool exit = false;

	SCREENS currentScreen = MENU;

	static void InitGame()
	{
		SetExitKey(0);
		InitWindow(screenWidth, screenHeight, "FlappyBirds");
		InitValues();
		InitMenu();
		InitCredits();
		InitGameover();
		InitPause();
		music = LoadMusicStream("res/menuMusic.mp3");
	}

	static void UpdateGame()
	{
		PlayMusicStream(music);
		switch (currentScreen)
		{
		case MENU:
			
			UpdateMusicStream(music);
			UpdateMenu();
			break;
		case GAMEPLAY:
			UpdateFrame();
			StopMusicStream(music);
			break;
		case GAMEOVER:
			UpdateGameOver();
			break;
		case CREDITS:
			
			UpdateMusicStream(music);
			UpdateCredits();
			break;
		case PAUSE:
			UpdatePause();
			break;
		default:
			break;
		}
	}

	static void DrawGame()
	{
		BeginDrawing();
		switch (currentScreen)
		{
		case MENU:
			DrawMenu();
			break;
		case GAMEPLAY:
			Draw();
			break;
		case GAMEOVER:
			DrawGameOver();
			break;
		case CREDITS:
			DrawCredits();
			break;
		case PAUSE:
			DrawPause();
			break;
		default:
			break;
		}
		EndDrawing();
	}

	static void CloseGame()
	{
		CloseWindow();
	}

	void ExecuteGame()
	{
		InitGame();

		while (!WindowShouldClose() && !exit)
		{
			UpdateGame();
			DrawGame();
		}
		CloseGame();
	}
}