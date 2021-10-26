#include "Obstacle.h"

#include "App.h"
#include "Player.h"
#include "Gameplay.h"

using namespace app;
using namespace gameplay;

namespace app
{
	namespace obstacle
	{
		static const int colGap = 250;
		static const int colSpeed = 300;
		static const int birdGap = 215;
		static const int minRand = 0;
		static const int maxRand = 250;

		static const int totalCols = 5;
		Column columnsUp[totalCols];
		Column columnsDown[totalCols];
		static int random;

		void InitObstacle()
		{
			for (int i = 0; i < totalCols; i++)
			{
				random = GetRandomValue(minRand, maxRand);

				//Up Cols
				columnsUp[i].texture = LoadTexture("res/COLUMN.png");

				columnsUp[i].position.x = GetScreenWidth() + colGap + (colGap + columnsUp[i].texture.width) * i;
				columnsUp[i].position.y = 0 - random;

				columnsUp[i].collider.height = columnsUp[i].texture.height;
				columnsUp[i].collider.width = columnsUp[i].texture.width;
				columnsUp[i].collider.x = 0;
				columnsUp[i].collider.y = 0;

				columnsUp[i].sourceRec = { 0.0f, 0.0f, (float)columnsUp[i].texture.width, (float)columnsUp[i].texture.height };

				columnsUp[i].destRec = { columnsUp[i].position.x, columnsUp[i].position.y, (float)columnsUp[i].texture.width,(float)columnsUp[i].texture.height };

				columnsUp[i].origin = { 0,0 };

				//Down Cols
				columnsDown[i].texture = LoadTexture("res/COLUMN.png");

				columnsDown[i].position.x = GetScreenWidth() + colGap + (colGap + columnsUp[i].texture.width) * i;
				columnsDown[i].position.y = columnsUp[i].position.y + columnsUp[i].texture.height + birdGap;

				columnsDown[i].collider.height = columnsUp[i].texture.height;
				columnsDown[i].collider.width = columnsUp[i].texture.width;
				columnsDown[i].collider.x = 0;
				columnsDown[i].collider.y = 0;

				columnsDown[i].sourceRec = { 0.0f, 0.0f, (float)columnsDown[i].texture.width, (float)columnsDown[i].texture.height };

				columnsDown[i].destRec = { columnsDown[i].position.x, columnsDown[i].position.y, (float)columnsDown[i].texture.width,(float)columnsDown[i].texture.height };

				columnsDown[i].origin = { (float)columnsDown[i].texture.width, (float)columnsDown[i].texture.height };
			}
		}

		void UpdateObstacle()
		{
			if (!gameOver)
			{
				for (int i = 0; i < totalCols; i++)
				{
					//Movement
					random = GetRandomValue(minRand, maxRand);

					columnsUp[i].position.x -= colSpeed * GetFrameTime();
					columnsDown[i].position.x -= colSpeed * GetFrameTime();

					columnsUp[i].collider.x = (int)columnsUp[i].position.x;
					columnsUp[i].collider.y = (int)columnsUp[i].position.y;

					columnsDown[i].collider.x = (int)columnsDown[i].position.x;
					columnsDown[i].collider.y = (int)columnsDown[i].position.y;

					//Collision player
					if (CheckCollisionCircleRec(player::player.position, player::player.radius, columnsUp[i].collider))
					{
						gameOver = true;
						player::player.isDead = true;
					}

					if (CheckCollisionCircleRec(player::player.position, player::player.radius, columnsDown[i].collider))
					{
						gameOver = true;
						player::player.isDead = true;
					}

					//Recicle
					if (columnsUp[i].position.x + columnsUp[i].texture.width <= 0) 
					{
						// recicle up
						columnsUp[i].position.y = 0 - random;
						if (i == 0)
						{
							columnsUp[i].position.x = columnsUp[totalCols - 1].position.x + colGap;

						}
						else
						{
							columnsUp[i].position.x = columnsUp[i - 1].position.x + colGap;
						}

						// recicle down
						columnsDown[i].position.y = columnsUp[i].position.y + columnsUp[i].texture.height + birdGap;
						columnsDown[i].position.x = columnsUp[i].position.x;
						
					}

					columnsDown[i].destRec = { columnsDown[i].position.x, columnsDown[i].position.y, (float)columnsDown[i].texture.width,(float)columnsDown[i].texture.height };

					columnsUp[i].destRec = { columnsUp[i].position.x, columnsUp[i].position.y, (float)columnsUp[i].texture.width,(float)columnsUp[i].texture.height };
				}
			}
		}

		void DrawObstacle()
		{
			for (int i = 0; i < totalCols; i++)
			{
				DrawTexturePro(columnsDown[i].texture, columnsDown[i].sourceRec, columnsDown[i].destRec, columnsDown[i].origin, 180, WHITE);
				DrawTexturePro(columnsUp[i].texture, columnsUp[i].sourceRec, columnsUp[i].destRec, columnsUp[i].origin, 0, WHITE);
			}
		}

		void UnloadObstacle()
		{
			for (int i = 0; i < totalCols; i++) 
			{
				UnloadTexture(columnsUp[i].texture);
				UnloadTexture(columnsDown[i].texture);
			}
		}
	}
}