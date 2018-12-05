#include "screen\Win\win.h"

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
	static  Rectangle recMenu;
	static Texture2D restart;
	static Texture2D negativeRestart;
	static Rectangle recRestart;
	static bool menuButtonAnimationOn;
	static bool exitButtonAnimationOn;
	static bool restartButtonAnimationOn;
	static bool firstInit = true;

	static void initWin()
	{
		if (firstInit)
		{
			firstInit = false;
			menu = LoadTexture("res/boton_menu.png");
			negativeMenu = LoadTexture("res/boton_menu2.png");
			exit = LoadTexture("res/exit.png");
			negativeExit = LoadTexture("res/exit2.png");
			fond = LoadTexture("res/menu.png");
			restart = LoadTexture("res/restart.png");
			negativeRestart = LoadTexture("res/restart2.png");
			recMenu = { (float)screenWidth / 2 - menu.width / 2,(float)screenHeight / 2 ,(float)menu.width,(float)menu.height };
			recExit = { (float)screenWidth / 2 - exit.width / 2,(float)screenHeight / 2 + exit.height*2 + 5,(float)exit.width,(float)exit.height };
			recRestart = { (float)screenWidth / 2 - restart.width / 2,(float)screenHeight / 2 + restart.height + 5,(float)restart.width,(float)restart.height };
		}
	}
	void UpdateWin()
	{
		initWin();
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
		if (CheckCollisionPointRec(GetMousePosition(), recRestart))
		{
			restartButtonAnimationOn = false;

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				screen = GAME;
			}
		}
		else
		{
			restartButtonAnimationOn = true;
		}
	}
	void DrawWin()
	{
		static int fontSizeTitle = 50;
		static int fontSize = 20;
		if (screenWidth >= 1600)
		{
			fontSize = 40;
			fontSizeTitle = 100;
		}
		DrawTexture(fond, 0, 0, WHITE);
		DrawText("You Win,Congrats!", screenWidth / 2 - (MeasureText("You Win,Congrats!", fontSizeTitle) / 2), screenHeight / 4, fontSizeTitle, GOLD);
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
			DrawTexture(exit, screenWidth / 2 - exit.width / 2, screenHeight / 2 + exit.height *2 + 5, WHITE);
		}
		else
		{
			DrawTexture(negativeExit, screenWidth / 2 - exit.width / 2, screenHeight / 2 + exit.height*2 + 5, WHITE);
		}
		if (restartButtonAnimationOn)
		{
			DrawTexture(restart, screenWidth / 2 - restart.width / 2, screenHeight / 2 + restart.height + 5, WHITE);
		}
		else
		{
			DrawTexture(negativeRestart, screenWidth / 2 - restart.width / 2, screenHeight / 2 + restart.height + 5, WHITE);
		}
	}
	void closeWin()
	{
		UnloadTexture(fond);
		UnloadTexture(menu);
		UnloadTexture(negativeMenu);
		UnloadTexture(exit);
		UnloadTexture(negativeExit);
	}
}