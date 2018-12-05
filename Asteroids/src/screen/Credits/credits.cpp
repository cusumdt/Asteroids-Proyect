#include"credits.h"

#include "raylib.h"

#include "screen\Gameplay\gameplay.h"
#include "Game\game.h"
namespace GameInit
{
	static Texture2D fond;
	static Texture2D menu;
	static Texture2D negativeMenu;
	static Rectangle recMenu;
	static int positionY = screenHeight / 4;
	static bool menuButtonAnimationOn;
	static bool exitButtonAnimationOn;
	static bool firstInit = true;
	static const int screenWidthLimit = 1600;
	static int fontSize = 20;
	static void initCredits()
	{
		if (firstInit)
		{
			firstInit = false;
			menu = LoadTexture("res/boton_menu.png");
			negativeMenu = LoadTexture("res/boton_menu2.png");
			fond = LoadTexture("res/menu.png");
			recMenu = { (float)screenWidth / 2 - menu.width / 2,(float)screenHeight / 2 + menu.height,(float)menu.width,(float)menu.height };
		}
	}
	void UpdateCredits()
	{
		initCredits();
		if (screenWidth >= screenWidthLimit)
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
	}
	void DrawCredits()
	{
		DrawTexture(fond, 0, 0, WHITE);
		if (menuButtonAnimationOn)
		{
			DrawTexture(menu, screenWidth / 2 - menu.width / 2, screenHeight / 2 + menu.height, WHITE);
		}
		else
		{
			DrawTexture(negativeMenu, screenWidth / 2 - negativeMenu.width / 2, screenHeight / 2 + menu.height, WHITE);
		}
		DrawText("Programmer: Cusumano Cristian", screenWidth / 2 - (MeasureText("Programmer: Cusumano Cristian", fontSize) / 2), positionY + fontSize * 2, fontSize, GOLD);
		DrawText("Music and Efects By: Cusumano Cristian", screenWidth / 2 - (MeasureText("Music and Efects By: Cusumano Cristian", fontSize) / 2), positionY + fontSize * 4 + 5, fontSize, GOLD);
		DrawText("Tools: Raylib - BoscaCeoil - MusicMaker - Photoshop", screenWidth / 2 - (MeasureText("Tools: Raylib - BoscaCeoil - MusicMaker - Photoshop", fontSize) / 2), positionY + fontSize * 6 + 5, fontSize, GOLD);
		DrawText("v1.1", screenWidth / 2 - (MeasureText("v1.1", fontSize) / 2), positionY + fontSize * 13 + 5, fontSize, GOLD);
	}
	void CloseCredits()
	{
		UnloadTexture(fond);
		UnloadTexture(menu);
		UnloadTexture(negativeMenu);
	}
}