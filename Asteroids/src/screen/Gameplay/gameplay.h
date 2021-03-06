#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace GameInit
{
		extern bool firstInit;
	
		extern bool left;
		extern bool right;
		void initGame();
		void updateGame();
		void DrawGame();
		struct Player {
			Texture2D player_texture;
			Vector2 position;
			Vector2 speed;
			Vector2 acceleration;
			float rotation;
			Vector3 collider;
			Color color;
			Rectangle sourceRec;
			Rectangle destRec;
			Vector2 origin;

		};
		extern Player player;
		extern float shipHeight;
		void CloseGameplay();
}
#endif