#include "player.h"

#include "Pause.h"
#include "Gameplay.h"
#include "App.h"
#include "Obstacle.h"

using namespace app;
using namespace gameplay;
using namespace pause;
using namespace obstacle;

namespace app
{
	namespace player
	{
		Player player;

		float delayTime = 0.1f;
		int currentFrame = 0;

		int gravity = 2000;
		int playerOnClickRotation = -45;
		int gravityRotation = 250;
		float playerSpeed = -400;

		static float timer;

		void InitPlayer()
		{
			player.flappyImage = LoadImage("res/BirdHero.png");

			player.flappyTexture = LoadTextureFromImage(player.flappyImage);

			player.position = { (float)GetScreenWidth() / 2 - player.flappyTexture.width / 2 - 200, (float)GetScreenHeight() / 2 - player.flappyTexture.height / 2 };
			player.color = WHITE;
			player.acceleration = { 0,0 };
			player.rotation = 0;
			player.speed.x = 0;
			player.speed.y = 0;
			player.radius = (float)(player.flappyTexture.width / 3) / 2 - 30;
			player.isDead = false;

			player.sourceRec = { 0.0f, 0.0f, (float)player.flappyTexture.width / 3, (float)player.flappyTexture.height };

			player.destRec = { player.position.x, player.position.y, (float)player.flappyTexture.width, (float)player.flappyTexture.height };

			player.origin = { ((float)player.flappyTexture.width / 3) / 2, (float)player.flappyTexture.height / 2};

			//FrameTimeCounter
			timer = GetFrameTime();
		}
		

		void UpdatePlayer()
		{
			timer += GetFrameTime();

			if (!gameOver)
			{
				PlayerController();
			}
			else
			{
				currentScreen = GAMEOVER;
			}
		}

		void DrawPlayer()
		{
			DrawTexturePro(player.flappyTexture, player.sourceRec, player.destRec, player.origin, player.rotation, player.color);
		}

		void UnloadPlayer()
		{
			UnloadTexture(player.flappyTexture);
		}

		void PlayerController()
		{
			// Player logic: acceleration
			if (IsKeyPressed('W') && !player.isDead)
			{
				if (player.position.y >= player.flappyTexture.height)
				{
					player.rotation = playerOnClickRotation;
					player.speed.y = playerSpeed;

					if (player.position.y <= player.flappyTexture.height)
					{
						player.position.y = player.flappyTexture.height;
					}

					currentFrame = 1;
					player.sourceRec.x = (float)currentFrame * (float)player.flappyTexture.width / 3;
					timer = 0;
				}
			}
			else
			{
				if (timer > delayTime)
				{
					if (player.rotation < 90)
					{
						player.rotation += gravityRotation * GetFrameTime();
					}

					currentFrame = 0;
					player.sourceRec.x = (float)currentFrame * (float)player.flappyTexture.width / 3;
				}
			}

			//player dead condition
			if (player.isDead)
			{
				currentFrame = 2;
				player.sourceRec.x = (float)currentFrame * (float)player.flappyTexture.width / 3;
				gameOver = true;
			}

			//player Gravity
			if (player.position.y != GetScreenHeight())
			{
				player.speed.y += gravity * GetFrameTime();
				player.position.y += player.speed.y * GetFrameTime();
			}

			// Collision logic: player vs ground
			if (player.position.y >= GetScreenHeight())
			{
				currentFrame = 2;
				player.sourceRec.x = (float)currentFrame * (float)player.flappyTexture.width / 3;
				player.position.y = GetScreenHeight();
				player.isDead = true;
			}

			//player refresh
			player.destRec = { player.position.x, player.position.y, (float)player.flappyTexture.width / 3, (float)player.flappyTexture.height };
		}
	}
}