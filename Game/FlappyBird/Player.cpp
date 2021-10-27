#include "player.h"

#include "Pause.h"
#include "Gameplay.h"
#include "App.h"
#include "Obstacle.h"
#include"Menu.h"

using namespace app;
using namespace gameplay;
using namespace pause;
using namespace obstacle;
using namespace menu;

namespace app
{
	namespace player
	{
		Player player;
		Player player2;

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
		void InitPlayer2()
		{
			player2.flappyImage = LoadImage("res/BirdHero2.png");

			player2.flappyTexture = LoadTextureFromImage(player2.flappyImage);

			player2.position = { (float)GetScreenWidth() / 2 - player2.flappyTexture.width / 2 - 100, (float)GetScreenHeight() / 2 - player2.flappyTexture.height / 2 };
			player2.color = WHITE;
			player2.acceleration = { 0,0 };
			player2.rotation = 0;
			player2.speed.x = 0;
			player2.speed.y = 0;
			player2.radius = (float)(player.flappyTexture.width / 3) / 2 - 30;
			player2.isDead = false;

			player2.sourceRec = { 0.0f, 0.0f, (float)player2.flappyTexture.width / 3, (float)player2.flappyTexture.height };

			player2.destRec = { player2.position.x, player2.position.y, (float)player2.flappyTexture.width, (float)player2.flappyTexture.height };

			player2.origin = { ((float)player2.flappyTexture.width / 3) / 2, (float)player2.flappyTexture.height / 2 };
		}

		void UpdatePlayer()
		{
			timer += GetFrameTime();

				PlayerController();
				/*Player2Controller();*/
			
		}
		void UpdatePlayer2()
		{
			timer += GetFrameTime();

	
			Player2Controller();

		}

		void DrawPlayer()
		{
			DrawTexturePro(player.flappyTexture, player.sourceRec, player.destRec, player.origin, player.rotation, player.color);
		}
		void DrawPlayer2()
		{
			DrawTexturePro(player2.flappyTexture, player2.sourceRec, player2.destRec, player2.origin, player2.rotation, player2.color);
		}

		void UnloadPlayer()
		{
			UnloadTexture(player.flappyTexture);
		}

		void UnloadPlayer2()
		{
			UnloadTexture(player2.flappyTexture);
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
				if (!isMultiplayer)
				{
					gameOver = true;
				}
				else 
				{
					if (player2.isDead)
					gameOver = true;
				}
				
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
				player.position.y = GetScreenHeight()+player.flappyTexture.width;
				player.isDead = true;
			}

			//player refresh
			player.destRec = { player.position.x, player.position.y, (float)player.flappyTexture.width / 3, (float)player.flappyTexture.height };
		}
		void Player2Controller()
		{
			if (IsKeyPressed(KEY_UP) && !player2.isDead)
			{
				if (player2.position.y >= player2.flappyTexture.height)
				{
					player2.rotation = playerOnClickRotation;
					player2.speed.y = playerSpeed;

					if (player2.position.y <= player2.flappyTexture.height)
					{
						player2.position.y = player2.flappyTexture.height;
					}

					currentFrame = 1;
					player2.sourceRec.x = (float)currentFrame * (float)player2.flappyTexture.width / 3;
					timer = 0;
				}
			}
			else
			{
				if (timer > delayTime)
				{
					if (player2.rotation < 90)
					{
						player2.rotation += gravityRotation * GetFrameTime();
					}

					currentFrame = 0;
					player2.sourceRec.x = (float)currentFrame * (float)player2.flappyTexture.width / 3;
				}
			}

			//player dead condition
			if (player2.isDead)
			{

				currentFrame = 2;
				player2.sourceRec.x = (float)currentFrame * (float)player2.flappyTexture.width / 3;
				if (player.isDead)
				{
					gameOver = true;

				}
				
			}

			//player Gravity
			if (player2.position.y != GetScreenHeight())
			{
				player2.speed.y += gravity * GetFrameTime();
				player2.position.y += player2.speed.y * GetFrameTime();
			}

			// Collision logic: player vs ground
			if (player2.position.y >= GetScreenHeight())
			{
				currentFrame = 2;
				player2.sourceRec.x = (float)currentFrame * (float)player2.flappyTexture.width / 3;
				player2.position.y = GetScreenHeight()+player.flappyTexture.width;
				player2.isDead = true;
			}

			//player refresh
			player2.destRec = { player2.position.x, player2.position.y, (float)player2.flappyTexture.width / 3, (float)player2.flappyTexture.height };
		}
	}
}