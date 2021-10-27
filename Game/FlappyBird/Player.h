#pragma once

#include "raylib.h"

namespace app
{
	namespace player
	{

		struct Player
		{
			Image flappyImage;
			Texture2D flappyTexture;
			Vector2 position;
			Vector2 speed;
			Color color;
			float radius;
			float rotation;
			Vector2 acceleration;
			bool isDead;
			Rectangle sourceRec;
			Rectangle destRec;
			Vector2 origin;
		};

		extern Player player;
		extern Player player2;

		void InitPlayer();
		void InitPlayer2();
		void UpdatePlayer();
		void UpdatePlayer2();
		void DrawPlayer();
		void DrawPlayer2();
		void UnloadPlayer(); 
		void UnloadPlayer2();
		void PlayerController();
		void Player2Controller();

	}
}