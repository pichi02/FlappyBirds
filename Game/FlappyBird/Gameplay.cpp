#include "Gameplay.h"

#include "raylib.h"
#include "App.h"
#include "Player.h"
#include "Obstacle.h"
#include "Parallax.h"
#include"Menu.h"

using namespace app;
using namespace player;
using namespace obstacle;
using namespace parallax;
using namespace menu;
namespace app
{
	namespace gameplay
	{
		extern bool gameOver = false;

		//Boton pausa
		static Rectangle btnPause1;
		static Rectangle btnPause2;
		static Color colorRect;
		static Vector2 mousePoint;
		float clock;
		const float controllerInstructionTime = 8;
		int p1TextPosY;
		int p1TextPosX;
		int p1ControllerTextX;
		int p1ControllerTextY;
		int p2TextPosY;
		int p2TextPosX;
		int p2ControllerTextX;
		int p2ControllerTextY;

		static bool init;

		void InitValues()
		{
			InitAudioDevice();

			clock = 0;
			p1TextPosY = (GetScreenHeight() / 100) * 2;
			p1TextPosX = (GetScreenWidth() / 100) * 2;
			p1ControllerTextX = p1TextPosX;
			p1ControllerTextY = p1TextPosY + (GetScreenHeight() / 100) * 4;
			p2TextPosY = p1TextPosY;
			p2ControllerTextY = p1ControllerTextY;
			p2ControllerTextX = p1ControllerTextX + (GetScreenWidth() / 100) * 12;
			p2TextPosX = p1TextPosX + (GetScreenWidth() / 100) * 12;
			//init boton pausa
			btnPause1.x = GetScreenWidth() * 0.96f;
			btnPause1.y = GetScreenHeight() * 0.02f;
			btnPause1.height = (GetScreenWidth() * 40) / 1600;
			btnPause1.width = (GetScreenWidth() * 15) / 1600;
			btnPause2.x = GetScreenWidth() * 0.975f;
			btnPause2.y = GetScreenHeight() * 0.02f;
			btnPause2.height = (GetScreenWidth() * 40) / 1600;
			btnPause2.width = (GetScreenWidth() * 15) / 1600;
			colorRect = GRAY;

			InitParallax();
			InitPlayer();
			InitPlayer2();
			InitObstacle();
		}

		static void Input()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, btnPause1))
			{
				colorRect.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = PAUSE;
			}
			else colorRect.a = 255;

			if (CheckCollisionPointRec(mousePoint, btnPause2))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = PAUSE;
				colorRect.a = 120;
			}
		}

		static void Update()
		{
			UpdateParallax();
			if (!gameOver)
			{
				UpdatePlayer();
				if (isMultiplayer)
				{
					UpdatePlayer2();
				}
			}
			else
			{
				currentScreen = GAMEOVER;
				ResetValues();
			}

			UpdateObstacle();
			clock += GetFrameTime();
		}

		void UpdateFrame()
		{
			Input();
			Update();
		}

		void Draw()
		{
			ClearBackground(BLANK);

			DrawParallax();
			DrawPlayer();
			if (isMultiplayer)
			{
				DrawPlayer2();
			}
			if (clock<controllerInstructionTime&&(int)clock%2==0)
			{
				if (!player::player.isDead)
				{
					DrawText("P1", p1ControllerTextX, p1TextPosY, 20, WHITE);
					DrawText("W to FLY", p1ControllerTextX, p1ControllerTextY, 15, WHITE);
				}
				if (isMultiplayer)
				{
					if (!player::player2.isDead)
					{
						DrawText("P2", p2TextPosX, p2TextPosY, 20, WHITE);
						DrawText("UP to FLY", p2ControllerTextX, p2ControllerTextY, 15, WHITE);
					}
				}

				
				
			}
			DrawObstacle();

			DrawRectangleRec(btnPause1, colorRect);
			DrawRectangleRec(btnPause2, colorRect);
		}

		void ResetValues()
		{
			InitValues();
			gameOver = false;


		}

		void UnloadGameplay()
		{
			DeInitParallax();
			UnloadPlayer();
			UnloadObstacle();
		}
	}
}