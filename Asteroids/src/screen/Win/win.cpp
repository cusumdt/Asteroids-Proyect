#include "screen\Win\win.h"
#include "Game\game.h"
#include "screen\Gameplay\gameplay.h"
#include "raylib.h"
namespace GameInit
{
	namespace initWin
	{
		void UpdateWin()
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				screen = MENU;
			}
			SetExitKey(KEY_ESCAPE);
		}
		void DrawWin()
		{
			static int fontSizeTitle = 50;
			static int fontSize = 20;
			if (Gameplay::screenWidth >= 1600)
			{
				fontSize = 40;
				fontSizeTitle = 100;
			}
			DrawText("You Win,Congrats!", Gameplay::screenWidth / 2 - (MeasureText("You Win,Congrats!", fontSizeTitle) / 2), Gameplay::screenHeight / 5, fontSizeTitle, GOLD);
			DrawRectangle(Gameplay::screenWidth / 2 - (MeasureText("Press Escape To Quit", fontSize) / 2) - 5, Gameplay::screenHeight / 3, MeasureText("Press Escape To Quit", fontSize) + 10, fontSize * 2 + 10, LIGHTGRAY);
			DrawRectangleLines(Gameplay::screenWidth / 2 - (MeasureText("Press Escape To Quit", fontSize) / 2) - 5, Gameplay::screenHeight / 3, MeasureText("Press Escape To Quit", fontSize) + 10, fontSize * 2 + 10, GOLD);
			DrawText("Press Space To Menu", Gameplay::screenWidth / 2 - (MeasureText("Press Space To Menu", fontSize) / 2), Gameplay::screenHeight / 3 + 5, fontSize, WHITE);
			DrawText("Press Scape To Quit", Gameplay::screenWidth / 2 - (MeasureText("Press Scape To Quit", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize + 5, fontSize, WHITE);
		}
	}
}