#include "screen\Defeat\defeat.h"
#include "Game\game.h"
#include "screen\Gameplay\gameplay.h"
#include "raylib.h"
namespace GameInit
{
	namespace initDefeat
	{
		Texture2D fond;
		Rectangle recExit;
		Texture2D exit;
		Texture2D negativeExit;
		Texture2D menu;
		Texture2D negativeMenu;
		Rectangle recMenu;
		static bool menuButtonAnimationOn;
		static bool exitButtonAnimationOn;
		static bool firstInit = true;
		void initDefeat() 
		{
			if (firstInit)
			{
				firstInit = false;
				menu = LoadTexture("res/play.png");
				negativeMenu = LoadTexture("res/play2.png");
				exit = LoadTexture("res/exit.png");
				negativeExit = LoadTexture("res/exit2.png");
				fond = LoadTexture("res/menu.png");
				recMenu = { (float)Gameplay::screenWidth / 2 - menu.width / 2,(float)Gameplay::screenHeight / 2 ,(float)menu.width,(float)menu.height };
				recExit = { (float)Gameplay::screenWidth / 2 - exit.width / 2,(float)Gameplay::screenHeight / 2 + exit.height + 5,(float)exit.width,(float)exit.height };
			}
		}
		void UpdateDefeat()
		{
			initDefeat();
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
		void DrawDefeat()
		{
			static int fontSizeTitle = 50;
			static int fontSize = 20;
			if (Gameplay::screenWidth >= 1600)
			{
				fontSize = 40;
				fontSizeTitle = 100;

			}
			DrawTexture(fond, 0, 0, WHITE);
			DrawText("You Lose!", Gameplay::screenWidth / 2 - (MeasureText("You Lose!", fontSizeTitle) / 2), Gameplay::screenHeight /4, fontSizeTitle, GOLD);
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
		}
	}
}