
#include "screen\Menu\menu.h"
#include "raylib.h"

#include "screen\Gameplay\gameplay.h"
#include "Game\game.h"
namespace GameInit
{
	bool music = true;
	namespace initMenu
	{
		static bool settings = false;
		static int fontSizeTitle = 0;
		static int fontSize = 0;
		static bool playButtonAnimationOn;
		Texture2D fond;
		Texture2D play;
		Texture2D negativePlay;
		Rectangle recplay;
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
			fond= LoadTexture("res/menu.png");
			play = LoadTexture("res/play.png");
			negativePlay= LoadTexture("res/play2.png");
			//recplay = {(float)play.width,(float)play.height,(float)Gameplay::screenWidth / 2 - play.width / 2 ,(float)Gameplay::screenHeight / 2 - play.height / 2 };
			recplay = {(float)Gameplay::screenWidth / 2 - play.width / 2,(float)Gameplay::screenHeight/2 -play.height /2,(float)play.width,(float)play.height};
		}
		
		static void drawFrame()
		{
			DrawRectangle(Gameplay::screenWidth / 2 - (MeasureText("Press S to Silence Music", fontSize) / 2) - 5, Gameplay::screenHeight / 3, MeasureText("Press S to Silence Music", fontSize) + 10, fontSize * 5 + 20, LIGHTGRAY);
			DrawRectangleLines(Gameplay::screenWidth / 2 - (MeasureText("Press S to Silence Music", fontSize) / 2) - 5, Gameplay::screenHeight / 3, MeasureText("Press S to Silence Music", fontSize) + 10, fontSize * 5 + 20, GOLD);
		}
		static void drawTextMenu() 
		{
			DrawTexture(fond, 0, 0, WHITE);
			if(playButtonAnimationOn)
			{
				DrawTexture(play, Gameplay::screenWidth / 2 - play.width/2, Gameplay::screenHeight / 2, WHITE);
			}
			else 
			{
				DrawTexture(negativePlay, Gameplay::screenWidth / 2 - negativePlay.width / 2, Gameplay::screenHeight / 2, WHITE);
			}
			/*DrawText("Press Space To Play", Gameplay::screenWidth / 2 - (MeasureText("Press Space To Play", fontSize) / 2), Gameplay::screenHeight / 3 + 5, fontSize, WHITE);
			DrawText("Press Escape To Quit", Gameplay::screenWidth / 2 - (MeasureText("Press Escape To Quit", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize + 5, fontSize, WHITE);
			DrawText("Press H to Help", Gameplay::screenWidth / 2 - (MeasureText("Press H To Help", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize * 2 + 5, fontSize, WHITE);
			DrawText("Press C to Credits", Gameplay::screenWidth / 2 - (MeasureText("Press C to Credits", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize * 3 + 5, fontSize, WHITE);
			
			if (music)
			{
				DrawText("Press S to Silence Music", Gameplay::screenWidth / 2 - (MeasureText("Press S to Silence Music", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize * 4 + 5, fontSize, WHITE);
			}
			else
			{
				DrawText("Press S to Play Music", Gameplay::screenWidth / 2 - (MeasureText("Press S to Play Music", fontSize) / 2), Gameplay::screenHeight / 3 + fontSize * 4 + 5, fontSize, WHITE);
			}
			*/
			DrawText("v0.4", Gameplay::screenWidth / 2 - (MeasureText("v1.0", 25) / 2), Gameplay::screenHeight - Gameplay::screenHeight / 20, 25, BLACK);
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


			if (IsKeyPressed(KEY_SPACE))
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
				
			}
			if (IsKeyPressed(KEY_S))
			{
				music=!music;

			}
			SetExitKey(KEY_ESCAPE);
			if (CheckCollisionPointRec(GetMousePosition(),recplay))
			{
				playButtonAnimationOn = false;
			}
			else 
			{
				playButtonAnimationOn = true;
			}
		}
		void DrawMenu()
		{
			initSize();
			drawFrame();
			drawTextMenu();
			
		}
	}
}