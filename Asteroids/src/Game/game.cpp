#include "Game\game.h"

#include "raylib.h"

#include "screen\Menu\menu.h"
#include "screen\Win\win.h"
#include "screen\Gameplay\gameplay.h"
#include "screen\Credits\credits.h"
#include "screen\Defeat\defeat.h"
//#define MUSIC_ON
namespace GameInit
{
	int screenWidth = 1600;
	int screenHeight = 900;
	static void Init();
	static void Update();
	static void Draw();
	static void Close();
	bool endGame = false;
	static Music MusicLoop;
	static void Init()
	{
		InitWindow(screenWidth, screenHeight, "Asteroids");
		InitAudioDevice();
		MusicLoop = LoadMusicStream("res/music.ogg");
		PlayMusicStream(MusicLoop);
	}

	static void Update()
	{
		if (music) 
		{
			UpdateMusicStream(MusicLoop);
		}
		switch (screen)
		{
		case GAME:
			if (firstInit)
			{


				initGame();
				firstInit = false;
			}
			updateGame();
			break;
		case MENU:
			UpdateMenu();
			break;
		case WIN:
			UpdateWin();
			break;
		case CREDITS:
			UpdateCredits();
			break;
		case DEFEAT:
			UpdateDefeat();
			break;
		default:
			break;
		}
	}
	
	static void Draw()
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		switch (screen)
		{
		case GAME:
			DrawGame();
			break;
		case MENU:
			DrawMenu();
			break;
		case WIN:
			DrawWin();
			break;
		case CREDITS:
			DrawCredits();
			break;
		case DEFEAT:
			DrawDefeat();
			break;
		}
		EndDrawing();
	}



	static void Close()
	{
			UnloadMusicStream(MusicLoop);   // Unload music stream buffers from RAM
			CloseGameplay();
			UnloadTextureMenu();
			closeWin();
			CloseDefeat();
			CloseAudioDevice();
			CloseWindow();
			CloseCredits();
	}
	 void LoadScreen()
	{
		Init();
		// Main game loop
		while (!WindowShouldClose() && !endGame)    // Detect window close button or ESC key
		{
			Update();
			Draw();
		}
		//--------------------------------------------------------------------------------------   
		Close();
		// Close window and OpenGL context
		//--------------------------------------------------------------------------------------
	}

}
