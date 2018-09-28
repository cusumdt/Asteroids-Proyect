
#include "screen\Menu\menu.h"
#include "raylib.h"

#include "screen\Gameplay\gameplay.h"
#include "Game\game.h"
namespace GameInit
{
	
	namespace initMenu
	{
		static bool settings = false;

		static int fontSizeTitle = 0;
		static int fontSize = 0;
		void initSize()
		{
			if (Gameplay::screenWidth >= 1600)
			{
				fontSize = 40;
				fontSizeTitle = 100;

			}
			else 
			{
				fontSizeTitle = 50;
				fontSize = 20;
			}
		
		}
		
		static void drawFrame()
		{
			DrawRectangle(Gameplay::screenWidth / 2 - (MeasureText("Press Escape To Quit", fontSize) / 2) - 5, Gameplay::screenHeight / 3, MeasureText("Press Escape To Quit", fontSize) + 10, fontSize * 4 + 20, LIGHTGRAY);
			DrawRectangleLines(Gameplay::screenWidth / 2 - (MeasureText("Press Escape To Quit", fontSize) / 2) - 5, Gameplay::screenHeight / 3, MeasureText("Press Escape To Quit", fontSize) + 10, fontSize * 4 + 20, GOLD);
		}
		static void drawTextMenu() 
		{
			DrawText("ASTEROIDS", Gameplay::screenWidth / 2 - (MeasureText("ASTEROIDS", fontSizeTitle) / 2), Gameplay::screenHeight / 5, fontSizeTitle, GOLD);
			DrawText("Press Space To Play", Gameplay::screenWidth / 2 - (MeasureText("Press Space To Play", fontSize) / 2), Gameplay::screenHeight / 3 + 5, fontSize, WHITE);
			DrawText("Press H to Help", Gameplay::screenWidth / 2 - (MeasureText("Press H To Help", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize * 2 + 5, fontSize, WHITE);
			DrawText("Press C to Credits", Gameplay::screenWidth / 2 - (MeasureText("Press C to Credits", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize * 3 + 5, fontSize, WHITE);
			DrawText("Press Escape To Quit", Gameplay::screenWidth / 2 - (MeasureText("Press Escape To Quit", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize + 5, fontSize, WHITE);
			DrawText("v1.0", Gameplay::screenWidth / 2 - (MeasureText("v1.0", 25) / 2), Gameplay::screenHeight - Gameplay::screenHeight / 20, 25, BLACK);
			if (settings)
			{
				DrawRectangle(Gameplay::screenWidth / 2 - (MeasureText(" Player 2: KeyUp -> Up / KeyDown -> Down ", fontSize) / 2) - 5, Gameplay::screenHeight - Gameplay::screenHeight / 3, MeasureText(" Player 2: KeyUp -> Up / KeyDown -> Down ", fontSize) + 10, fontSize * 3 + 15, LIGHTGRAY);
				DrawRectangleLines(Gameplay::screenWidth / 2 - (MeasureText(" Player 2: KeyUp -> Up / KeyDown -> Down ", fontSize) / 2) - 5, Gameplay::screenHeight - Gameplay::screenHeight / 3, MeasureText(" Player 2: KeyUp -> Up / KeyDown -> Down ", fontSize) + 10, fontSize * 3 + 15, GOLD);
				DrawText("KeyUp -> Up / KeyDown -> Down", Gameplay::screenWidth / 2 - (MeasureText("KeyUp -> Up / KeyDown -> Down", fontSize) / 2), Gameplay::screenHeight - Gameplay::screenHeight / 3 + 5, fontSize, WHITE);
				DrawText("Space -> Shoot", Gameplay::screenWidth / 2 - (MeasureText("Space -> Shoot", fontSize) / 2), Gameplay::screenHeight - Gameplay::screenHeight / 3 + fontSize * 2 + 5, fontSize, WHITE);
			}
		}
		
		void UpdateMenu()
		{


			if (IsKeyDown(KEY_SPACE))
			{
				screen = GAME;
			}
			if (IsKeyPressed(KEY_H))
			{
				settings = !settings;
			}
			if (IsKeyPressed(KEY_C))
			{
				screen = CREDITS;
			}
			if (settings) 
			{
				if (IsKeyPressed(KEY_UP)) 
				{
				
				}
			}
			SetExitKey(KEY_ESCAPE);
		}
		void DrawMenu()
		{
			initSize();
			drawFrame();
			drawTextMenu();
			
		}
	}
}