#include"credits.h"
#include "raylib.h"
#include "screen\Gameplay\gameplay.h"
#include "Game\game.h"
namespace GameInit
{
	namespace initCredits
	{
		static int positionY = Gameplay::screenHeight / 2;
		static const int velocityCredits = 100;
		
		static int fontSize = 20;
		void UpdateCredits()
		{
			if (IsKeyDown(KEY_M))
			{
				screen = MENU;
			}
			if (Gameplay::screenWidth >= 1600)
			{
				fontSize = 40;
			}
			else 
			{
				fontSize = 20;
			}
			positionY -= velocityCredits * GetFrameTime();
			if (positionY<0-fontSize * 2)
			{
				positionY = Gameplay::screenHeight; 
			}
		}
		void DrawCredits() 
		{
			
			DrawText("Programmer: Cusumano Cristian", Gameplay::screenWidth / 2 - (MeasureText("Programmer: Cusumano Cristian", fontSize) / 2), positionY , fontSize, GOLD);
			DrawText("Music and Efects By: Cusumano Cristian", Gameplay::screenWidth / 2 - (MeasureText("Music and Efects By: Cusumano Cristian", fontSize) / 2), positionY + fontSize*2 + 5, fontSize, GOLD);
			DrawText("Tools: Raylib - BoscaCeoil - MusicMaker", Gameplay::screenWidth / 2 - (MeasureText("Tools: Raylib - BoscaCeoil - MusicMaker", fontSize) / 2), positionY + fontSize * 4 + 5, fontSize, GOLD);
			DrawText("v0.4", Gameplay::screenWidth / 2 - (MeasureText("v1.0", fontSize) / 2), positionY + fontSize * 6 + 5, fontSize, GOLD);
			DrawText("PRESS M FOR RETURN TO THE MENU", Gameplay::screenWidth / 2 - (MeasureText("PRESS M FOR RETURN TO THE MENU", 18) / 2), Gameplay::screenHeight - Gameplay::screenHeight / 20, 18, BLACK);
		}
	}
}