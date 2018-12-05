#include "screen\Defeat\defeat.h"

#include "raylib.h"

#include "Game\game.h"
#include "screen\Gameplay\gameplay.h"

namespace GameInit
{
	static Texture2D fond;
	static Rectangle recExit;
	static Texture2D exit;
	static Texture2D negativeExit;
	static Texture2D menu;
	static Texture2D negativeMenu;
	static Rectangle recMenu;
	static bool menuButtonAnimationOn;
	static bool exitButtonAnimationOn;
	static bool firstInit = true;
	static 	void initDefeat()
	{
		if (firstInit)
		{
			firstInit = false;
			menu = LoadTexture("res/boton_menu.png");
			negativeMenu = LoadTexture("res/boton_menu2.png");
			exit = LoadTexture("res/exit.png");
			negativeExit = LoadTexture("res/exit2.png");
			fond = LoadTexture("res/menu.png");
			recMenu = { (float)screenWidth / 2 - menu.width / 2,(float)screenHeight / 2 ,(float)menu.width,(float)menu.height };
			recExit = { (float)screenWidth / 2 - exit.width / 2,(float)screenHeight / 2 + exit.height + 5,(float)exit.width,(float)exit.height };
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
		if (screenWidth >= 1600)
		{
			fontSize = 40;
			fontSizeTitle = 100;

		}
		DrawTexture(fond, 0, 0, WHITE);
		DrawText("You Lose!", screenWidth / 2 - (MeasureText("You Lose!", fontSizeTitle) / 2), screenHeight / 4, fontSizeTitle, GOLD);
		if (menuButtonAnimationOn)
		{
			DrawTexture(menu, screenWidth / 2 - menu.width / 2, screenHeight / 2, WHITE);
		}
		else
		{
			DrawTexture(negativeMenu, screenWidth / 2 - negativeMenu.width / 2, screenHeight / 2, WHITE);
		}
		if (exitButtonAnimationOn)
		{
			DrawTexture(exit, screenWidth / 2 - exit.width / 2, screenHeight / 2 + exit.height + 5, WHITE);
		}
		else
		{
			DrawTexture(negativeExit, screenWidth / 2 - exit.width / 2, screenHeight / 2 + exit.height + 5, WHITE);
		}
	}
	void CloseDefeat()
	{
		UnloadTexture(fond);
		UnloadTexture(menu);
		UnloadTexture(negativeMenu);
		UnloadTexture(exit);
		UnloadTexture(negativeExit);
	}
}