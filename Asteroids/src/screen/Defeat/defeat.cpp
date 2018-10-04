#include "screen\Defeat\defeat.h"
#include "Game\game.h"
#include "screen\Gameplay\gameplay.h"
#include "raylib.h"
namespace GameInit
{
	namespace initDefeat
	{
		void UpdateDefeat()
		{
			if (IsKeyDown(KEY_SPACE))
			{
				screen = MENU;
			}
			SetExitKey(KEY_ESCAPE);
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

			DrawText("You Lose!", Gameplay::screenWidth / 2 - (MeasureText("You Lose!", fontSizeTitle) / 2), Gameplay::screenHeight / 5, fontSizeTitle, GOLD);
			DrawRectangle(Gameplay::screenWidth / 2 - (MeasureText("Press Escape To Quit", fontSize) / 2) - 5, Gameplay::screenHeight / 3, MeasureText("Press Escape To Quit", fontSize) + 10, fontSize * 2 + 10, LIGHTGRAY);
			DrawRectangleLines(Gameplay::screenWidth / 2 - (MeasureText("Press Escape To Quit", fontSize) / 2) - 5, Gameplay::screenHeight / 3, MeasureText("Press Escape To Quit", fontSize) + 10, fontSize * 2 + 10, GOLD);
			DrawText("Press Space To Play", Gameplay::screenWidth / 2 - (MeasureText("Press Space To Play", fontSize) / 2), Gameplay::screenHeight / 3 + 5, fontSize, WHITE);
			DrawText("Press Scape To Quit", Gameplay::screenWidth / 2 - (MeasureText("Press Scape To Quit", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize + 5, fontSize, WHITE);
		}
	}
}