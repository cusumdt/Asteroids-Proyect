#include "mov_ship.h"

#include "raylib.h"

#include "screen/Gameplay/gameplay.h"
#include <ctime>
#include <iostream>
#include <cmath>
namespace GameInit 
{
	namespace Logic_ship 
	{
		void mov_ship()
		{
			using namespace Gameplay;
			if (IsKeyDown(KEY_LEFT)) player.rotation -= 300 * GetFrameTime();
			if (IsKeyDown(KEY_RIGHT)) player.rotation += 300 * GetFrameTime();
			//player.speed.x = sin(player.rotation*DEG2RAD);
			
			player.speed.x = sin(player.rotation*DEG2RAD);
			player.speed.y = cos(player.rotation*DEG2RAD);
			//player.speed.y = cos(player.rotation*DEG2RAD);
			if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
			{
				if (player.acceleration < 1) player.acceleration += 300;
			}
			else
			{
				if (player.acceleration > 0) player.acceleration -= 150;
				else if (player.acceleration < 0) player.acceleration = 0;
			}
			if (IsKeyDown(KEY_DOWN))
			{
				if (player.acceleration > 0) player.acceleration -= 300;
				else if (player.acceleration < 0) player.acceleration = 0;
			}

			player.position.x += (player.speed.x*player.acceleration)* GetFrameTime();
			player.position.y -= (player.speed.y*player.acceleration)* GetFrameTime();
			if (player.position.x > screenWidth + shipHeight) player.position.x = -(shipHeight);
			else if (player.position.x < -(shipHeight)) player.position.x = screenWidth + shipHeight;
			if (player.position.y >(screenHeight + shipHeight)) player.position.y = -(shipHeight);
			else if (player.position.y < -(shipHeight)) player.position.y = screenHeight + shipHeight;
		}
	}
}
