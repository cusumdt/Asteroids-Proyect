#include"credits.h"

#include "raylib.h"

#include "screen\Gameplay\gameplay.h"
#include "Game\game.h"
namespace GameInit
{
	namespace initCredits
	{
		Texture2D fond;
		Rectangle recExit;
		Texture2D exit;
		Texture2D negativeExit;
		Texture2D menu;
		Texture2D negativeMenu;
		Rectangle recMenu;
		static int positionY = Gameplay::screenHeight / 4;
		static bool menuButtonAnimationOn;
		static bool exitButtonAnimationOn;
		static bool firstInit = true;
		
		static int fontSize = 20;
		void initCredits() 
		{
			if (firstInit)
			{
				firstInit = false;
				menu = LoadTexture("res/boton_menu.png");
				negativeMenu = LoadTexture("res/boton_menu2.png");
				exit = LoadTexture("res/exit.png");
				negativeExit = LoadTexture("res/exit2.png");
				fond = LoadTexture("res/menu.png");
				recMenu = { (float)Gameplay::screenWidth / 2 - menu.width / 2,(float)Gameplay::screenHeight / 2 ,(float)menu.width,(float)menu.height };
				recExit = { (float)Gameplay::screenWidth / 2 - exit.width / 2,(float)Gameplay::screenHeight / 2 + exit.height + 5,(float)exit.width,(float)exit.height };
			}
		}
		void UpdateCredits()
		{
			initCredits();
			if (Gameplay::screenWidth >= 1600)
			{
				fontSize = 40;
			}
			else 
			{
				fontSize = 20;
			}
			if (CheckCollisionPointRec(GetMousePosition(), recMenu))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					screen = MENU;
				}
				menuButtonAnimationOn = false;
			}
			else
			{
				menuButtonAnimationOn = true;
			}
			if (CheckCollisionPointRec(GetMousePosition(), recExit))
			{
				exitButtonAnimationOn = false;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					GameInit::endGame = !GameInit::endGame;
				}
			}
			else
			{
				exitButtonAnimationOn = true;
			}
		}
		void DrawCredits() 
		{
			DrawTexture(fond, 0, 0, WHITE);
			if (menuButtonAnimationOn)
			{
				DrawTexture(menu, Gameplay::screenWidth / 2 - menu.width / 2, Gameplay::screenHeight / 2, WHITE);
			}
			else
			{
				DrawTexture(negativeMenu, Gameplay::screenWidth / 2 - negativeMenu.width / 2, Gameplay::screenHeight / 2, WHITE);
			}
			if (exitButtonAnimationOn)
			{
				DrawTexture(exit, Gameplay::screenWidth / 2 - exit.width / 2, Gameplay::screenHeight / 2 + exit.height + 5, WHITE);
			}
			else
			{
				DrawTexture(negativeExit, Gameplay::screenWidth / 2 - exit.width / 2, Gameplay::screenHeight / 2 + exit.height + 5, WHITE);
			}
			DrawText("Programmer: Cusumano Cristian", Gameplay::screenWidth / 2 - (MeasureText("Programmer: Cusumano Cristian", fontSize) / 2), positionY , fontSize, GOLD);
			DrawText("Music and Efects By: Cusumano Cristian", Gameplay::screenWidth / 2 - (MeasureText("Music and Efects By: Cusumano Cristian", fontSize) / 2), positionY + fontSize*2 + 5, fontSize, GOLD);
			DrawText("Tools: Raylib - BoscaCeoil - MusicMaker - Photoshop", Gameplay::screenWidth / 2 - (MeasureText("Tools: Raylib - BoscaCeoil - MusicMaker - Photoshop", fontSize) / 2), positionY + fontSize * 4 + 5, fontSize, GOLD);
			DrawText("v0.4", Gameplay::screenWidth / 2 - (MeasureText("v1.0", fontSize) / 2), positionY + fontSize * 13 + 5, fontSize, GOLD);
		}
	}
}