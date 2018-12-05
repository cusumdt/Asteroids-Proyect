#include "mov_ship.h"

#include <ctime>
#include <iostream>
#include <cmath>

#include "raylib.h"
#include "Game\game.h"
#include "screen/Gameplay/gameplay.h"

namespace GameInit 
{
	namespace Logic_ship 
	{
		void mov_ship()
		{
			static float delta_y;
			static float delta_x;
			delta_y = player.destRec.y - GetMouseY();
			delta_x = player.destRec.x - GetMouseX();
			player.rotation = (atan2(delta_y, delta_x)*RAD2DEG)-90;
			player.speed.x = sin(player.rotation*DEG2RAD);
			player.speed.y = cos(player.rotation*DEG2RAD);
			if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
			{
				if (player.acceleration < 400) player.acceleration = 400;
			}
			else
			{
				if (player.acceleration > 200) player.acceleration -= 0.5f;
				else
				{
					player.acceleration = 200;
				}
			}
			player.position.x += (player.speed.x*player.acceleration)* GetFrameTime();
			player.position.y -= (player.speed.y*player.acceleration)* GetFrameTime();
			if (player.position.x > screenWidth + shipHeight) 
			{
				player.position.x = -(shipHeight);
			}
			else if (player.position.x < -(shipHeight))
			{
				player.position.x = screenWidth + shipHeight;
			}
			if (player.position.y > (screenHeight + shipHeight)) 
			{
				player.position.y = -(shipHeight);
			}
			else if (player.position.y < -(shipHeight))
			{
				player.position.y = screenHeight + shipHeight;
			}
		}
	}
}
