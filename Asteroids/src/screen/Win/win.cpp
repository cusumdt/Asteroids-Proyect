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
			if (IsKeyDown(KEY_SPACE))
			{
				screen = GAME;
			}
			SetExitKey(KEY_ESCAPE);
		}
		void DrawWin(bool left, bool right)
		{
			static int fontSizeTitle = 50;
			static int fontSize = 20;
			if (Gameplay::screenWidth >= 1600)
			{
				fontSize = 40;
				fontSizeTitle = 100;

			}
			if (left) DrawText("Left Player Win,Congrats!", Gameplay::screenWidth / 2 - (MeasureText("Left Player Win,Congrats!", fontSizeTitle) / 2), Gameplay::screenHeight / 5, fontSizeTitle, GOLD);
			else if (right) DrawText("Right Player Win,Congrats!", Gameplay::screenWidth / 2 - (MeasureText("Right Player Win,Congrats!", fontSizeTitle) / 2), Gameplay::screenHeight / 5, fontSizeTitle, GOLD);
			DrawRectangle(Gameplay::screenWidth / 2 - (MeasureText("Press Escape To Quit", fontSize) / 2) - 5, Gameplay::screenHeight / 3, MeasureText("Press Escape To Quit", fontSize) + 10, fontSize * 2 + 10, LIGHTGRAY);
			DrawRectangleLines(Gameplay::screenWidth / 2 - (MeasureText("Press Escape To Quit", fontSize) / 2) - 5, Gameplay::screenHeight / 3, MeasureText("Press Escape To Quit", fontSize) + 10, fontSize * 2 + 10, GOLD);
			DrawText("Press Space To Play", Gameplay::screenWidth / 2 - (MeasureText("Press Space To Play", fontSize) / 2), Gameplay::screenHeight / 3 + 5, fontSize, WHITE);
			DrawText("Press Scape To Quit", Gameplay::screenWidth / 2 - (MeasureText("Press Scape To Quit", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize + 5, fontSize, WHITE);
		}
	}
}