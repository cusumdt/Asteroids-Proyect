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
	Music MusicLoop;
	void Init() 
	{
		InitWindow(screenWidth, screenHeight, "Asteroids");
		InitAudioDevice();
		MusicLoop = LoadMusicStream("res/music.ogg");
		PlayMusicStream(MusicLoop);
	}

	void Update() 
	{
		if (music) 
		{
			UpdateMusicStream(MusicLoop);
		}
		switch (screen)
		{
		case GAME:
			if (Gameplay::firstInit)
			{


				Gameplay::initGame();
				Gameplay::firstInit = false;
			}
			Gameplay::updateGame();
			break;
		case MENU:
			initMenu::UpdateMenu();
			break;
		case WIN:
			initWin::UpdateWin();
			break;
		case CREDITS:
			initCredits::UpdateCredits();
			break;
		case DEFEAT:
			initDefeat::UpdateDefeat();
			break;
		default:
			break;
		}
	}
	
	void Draw() {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		switch (screen)
		{
		case GAME:
			Gameplay::DrawGame();
			break;
		case MENU:
			initMenu::DrawMenu();
			break;
		case WIN:
			initWin::DrawWin();
			break;
		case CREDITS:
			initCredits::DrawCredits();
			break;
		case DEFEAT:
			initDefeat::DrawDefeat();
			break;
		}
		EndDrawing();
	}



	void Close() {
			UnloadMusicStream(MusicLoop);   // Unload music stream buffers from RAM
			Gameplay::CloseGameplay();
			initMenu::UnloadTextureMenu();
			initWin::closeWin();
			initDefeat::CloseDefeat();
			CloseAudioDevice();
			CloseWindow();
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
