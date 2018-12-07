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
			static const short int ANGLE = 90;
			static const float velocity = 0.10f;
			static Vector2 positionMouse;
			static Vector2 vectorPosition;//vector de la posicion al mouse
			static Vector2 vPositionNormalized;
			float modVectorPosition;
			positionMouse = GetMousePosition();
			vectorPosition = { positionMouse.x - player.position.x  , positionMouse.y - player.position.y };

			player.rotation = (atan2(vectorPosition.y, vectorPosition.x)*RAD2DEG) + ANGLE;
			if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) 
			{
				modVectorPosition = sqrt(pow(vectorPosition.x, 2) + pow(vectorPosition.y, 2));
				vPositionNormalized.y = vectorPosition.y / modVectorPosition;
				vPositionNormalized.x = vectorPosition.x / modVectorPosition;
				player.acceleration.y += vPositionNormalized.y*velocity;
				player.acceleration.x += vPositionNormalized.x*velocity;
			}
			
			player.position.y += player.acceleration.y * GetFrameTime();
			player.position.x += player.acceleration.x * GetFrameTime();


			if (player.position.y >(GetScreenHeight() + shipHeight)) 
			{
				player.position.y = -(shipHeight);
			}

			else if (player.position.y < -(shipHeight)) 
			{
				player.position.y = GetScreenHeight() + shipHeight;
			}

			if (player.position.x > GetScreenWidth() +shipHeight) 
			{
				player.position.x = -(shipHeight);
			}

			else if (player.position.x < -(shipHeight)) 
			{
				player.position.x = GetScreenWidth() + shipHeight;
			}
			std::cout << player.position.x << std::endl;
		}
	}
}
