#include "gameplay.h"


#include <ctime>
#include <iostream>

#include "raylib.h"
#include "Game\game.h"
#include "Logic\mov_ship.h"

//#define MUSIC_ON
namespace GameInit
{
	Screen screen = MENU;
	Texture2D fond;
	enum Direction
	{
		Up = 1,
		Right,
		Left,
		Down,
		UpRight,
		UpLeft,
		DownRight,
		DownLeft
	};
	enum Limits {
		LimitTop = 1,
		LimitDown,
		LimitRight,
		LimitLeft
	};
	struct Meteor {
		Texture2D meteor_texture;
		float x;
		float y;
		Vector2 position;
		Vector2 speed;
		int radius;
		bool active;
		Direction dir;
		Rectangle sourceRec;
		Rectangle destRec;
		Vector2 origin;
	};

	struct Shoot {
		Vector2 position;
		Vector2 speed;
		float radius;
		float rotation;
		int lifeSpawn;
		bool active;
		Color color;
	};

	static Rectangle recExit;
	static Texture2D exit;
	static Texture2D negativeExit;
	static Texture2D menu;
	static Texture2D negativeMenu;
	static Texture2D asteroids;
	static Texture2D fond_black;
	static Rectangle recMenu;
	static Texture2D boton_pause;
	static Texture2D negativePause;
	static Rectangle recPause;
	static Texture2D restart;
	static Texture2D negativeRestart;
	static Rectangle recRestart;
	static bool pauseButtonAnimationOn;
	static bool menuButtonAnimationOn;
	static bool exitButtonAnimationOn;
	static bool restartButtonAnimationOn;
	static void initMeteor(Meteor meteor[]);
	static void drawMeteor(Meteor meteor[]);
	static void checkColisionMeteor(Meteor meteor[]);
	static void movMeteor(Meteor meteor[]);
	static void instanceThisMeteor(Meteor meteor[], int thisMeteor);
	static void initShoot(Shoot shoot[]);
	static void victory();
	static void defeat();
	static void restartPlayer();
	// Initialization
	//-------------------------------------------- Statics
	static int checkGame = 1;
	static const int TOTAL_METEOR = 10;
	static Rectangle box2;
	static Meteor meteor[TOTAL_METEOR];
	static short int INIT_VELOCITY = 400;
	static short int randomMusic = 0;
	static const short int MAX_POINT = 5;
	static const short int HEIGHT_BOX = (screenHeight / 15);
	static const short int WIDTH_BOX = (screenWidth / 25);
	static const short int RADIUS_BALL = (screenWidth / 45);
	static const short int SPEED_BALL_INIT = 0;
	static const short int MOVE_BOX = 400;
	static const short int INIT_SCORE = 0;
	static const short int LIMIT_TOP = 10;
	static const short int EXTRA_VELOCITY = 20;
	static const short int PLAYER_MAX_SHOOTS = 5;
	static Sound fxWav;
	static Sound fxWav2;
	static Sound fxWav3;
	static Sound fxWav4;
	static int velocity = INIT_VELOCITY;
	Player player;
	float shipHeight;
	static const float PLAYER_BASE_SIZE = 20.0f;
	static const float PLAYER_SPEED = 300.0f;
	static Shoot shoot[PLAYER_MAX_SHOOTS];
	static short int points = 0;
	static bool pause;
	static bool firstStart = true;
	static float timeDefeat = 0.0f;
	static bool defeatStatus = false;
	//--------------------------------------------

	static bool left = false;
	static bool right = false;
	bool firstInit = true;
	//--------------------------------------------
	void initGame() {
		fond = LoadTexture("res/fondo.png");
		fxWav = LoadSound("res/Blip_Select.wav");
		fxWav2 = LoadSound("res/Blip_Select2.wav");
		fxWav3 = LoadSound("res/Blip_Select3.wav");
		fxWav4 = LoadSound("res/Blip_Select4.wav");
		velocity = INIT_VELOCITY;
		//--------------------------------
		shipHeight = (PLAYER_BASE_SIZE / 2) / tanf(20 * DEG2RAD);
		player.player_texture = LoadTexture("res/Space_Ship.png");
		player.position = Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
		player.speed = Vector2{ 0, 0 };
		player.acceleration = { 0,0 };
		player.rotation = 0;
		player.sourceRec = { 0.0f,0.0f,(float)player.player_texture.width,(float)player.player_texture.height };
		player.destRec = { player.position.x,player.position.y,(float)player.player_texture.width,(float)player.player_texture.height };
		player.origin = { (float)player.player_texture.width / 2,(float)player.player_texture.height / 2 };
		player.collider = Vector3{ player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight / 2.5f), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight / 2.5f), 12 };
		player.color = LIGHTGRAY;
		//--------------------------------
		meteor[0].meteor_texture = LoadTexture("res/meteor.png");
		initMeteor(meteor);
		initShoot(shoot);
		menu = LoadTexture("res/boton_menu.png");
		negativeMenu = LoadTexture("res/boton_menu2.png");
		exit = LoadTexture("res/return.png");
		negativeExit = LoadTexture("res/return2.png");
		fond_black = LoadTexture("res/fondo_oscuridad.png");
		asteroids = LoadTexture("res/asteroids.png");
		boton_pause = LoadTexture("res/pause.png");
		negativePause = LoadTexture("res/pause2.png");
		restart = LoadTexture("res/restart.png");
		negativeRestart = LoadTexture("res/restart2.png");
		recMenu = { (float)screenWidth / 2 - menu.width / 2,(float)screenHeight / 2 ,(float)menu.width,(float)menu.height };
		recExit = { (float)screenWidth / 2 - exit.width / 2,(float)screenHeight / 2 + exit.height * 2 + 5,(float)exit.width,(float)exit.height };
		recPause = { (float)screenWidth - 100, (float)5,(float)boton_pause.width,(float)boton_pause.height };
		recRestart = { (float)screenWidth / 2 - restart.width / 2,(float)screenHeight / 2 + exit.height + 5 ,(float)restart.width,(float)restart.height };
	}


	void updateGame()
	{
		if (!pause)
		{
			if (defeatStatus)
			{
				timeDefeat += 1 * GetFrameTime();
				defeat();
			}
			if (CheckCollisionPointRec(GetMousePosition(), recPause))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					pause = !pause;
				}
				pauseButtonAnimationOn = false;
			}
			else
			{
				pauseButtonAnimationOn = true;
			}
			victory();
			SetExitKey(0);

			if (IsKeyDown(KEY_M))
			{
				pause = !pause;
			}
			//---------------------------------------------------------
			//Meteor Movement

			//---------------------------------------------------------
			//Bordes pantalla
			for (int i = 0; i < TOTAL_METEOR; i++)
			{
				if (meteor[i].y <= (LIMIT_TOP - RADIUS_BALL * 4) ||
					meteor[i].y >= (screenHeight + RADIUS_BALL * 4) ||
					meteor[i].x >= (screenWidth + RADIUS_BALL * 4) ||
					meteor[i].x <= (0 - RADIUS_BALL * 4))
				{
					instanceThisMeteor(meteor, i);
				}

			}
			//--------------------------------------------------------

			for (int i = 0; i < TOTAL_METEOR; i++)
			{
				meteor[i].position = Vector2{ meteor[i].x, meteor[i].y };
			}
			//-------------------------------------------------------


			if (!firstStart) {
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
					{
						if (!shoot[i].active)
						{
							shoot[i].position = Vector2{ player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight) };
							shoot[i].active = true;
							shoot[i].speed.x = 1.5*sin(player.rotation*DEG2RAD)*PLAYER_SPEED;
							shoot[i].speed.y = 1.5*cos(player.rotation*DEG2RAD)*PLAYER_SPEED;
							shoot[i].rotation = player.rotation;
							i = PLAYER_MAX_SHOOTS;
						}
					}
				}
				movMeteor(meteor);
				Logic_ship::mov_ship();
				checkColisionMeteor(meteor);
			}
			if (IsKeyDown(KEY_SPACE)) {
				firstStart = false;
			}

			// Shoot life timer
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
			{
				if (shoot[i].active)
				{
					shoot[i].lifeSpawn += 1 * GetFrameTime();
				}
			}

			// Shoot logic
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
			{
				if (shoot[i].active)
				{
					// Movement
					shoot[i].position.x += shoot[i].speed.x* GetFrameTime();
					shoot[i].position.y -= shoot[i].speed.y* GetFrameTime();

					// Collision logic: shoot vs walls
					if (shoot[i].position.x > screenWidth + shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					else if (shoot[i].position.x < 0 - shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					if (shoot[i].position.y > screenHeight + shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					else if (shoot[i].position.y < 0 - shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					// Life of shoot
					if (shoot[i].lifeSpawn >= 60)
					{
						shoot[i].position = Vector2{ 0, 0 };
						shoot[i].speed = Vector2{ 0, 0 };
						shoot[i].lifeSpawn = 0;
						shoot[i].active = false;
					}
				}
			}
			for (int i = 0; i < TOTAL_METEOR; i++)
			{
				meteor[i].destRec = { meteor[i].x,meteor[i].y,(float)meteor[0].meteor_texture.width,(float)meteor[0].meteor_texture.height };
			}
			player.destRec = { player.position.x,player.position.y,(float)player.player_texture.width,(float)player.player_texture.height };
		}
		else
		{
			if (CheckCollisionPointRec(GetMousePosition(), recMenu))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
						shoot[i].active = false;
					}
					restartPlayer();
					firstStart = true;
					initMeteor(meteor);
					points = INIT_SCORE;
					player.position = Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
					player.rotation = 0;
					pause = !pause;
					screen = MENU;
				}
				menuButtonAnimationOn = false;
			}
			else
			{
				menuButtonAnimationOn = true;
			}
			if (CheckCollisionPointRec(GetMousePosition(), recRestart))
			{
				restartButtonAnimationOn = false;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
						shoot[i].active = false;
					}
					restartPlayer();
					firstStart = true;
					initMeteor(meteor);
					points = INIT_SCORE;
					player.position = Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
					player.rotation = 0;
					pause = !pause;
				}
			}
			else
			{
				restartButtonAnimationOn = true;
			}
			if (CheckCollisionPointRec(GetMousePosition(), recExit))
			{
				exitButtonAnimationOn = false;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					pause = !pause;
				}
			}
			else
			{
				exitButtonAnimationOn = true;
			}
		}
	}
	void DrawGame()
	{
		DrawTexture(fond, 0, 0, WHITE);
		if (pauseButtonAnimationOn)
		{
			DrawTexture(boton_pause, screenWidth - 100, 5, WHITE);
		}
		else
		{
			DrawTexture(negativePause, screenWidth - 100, 5, WHITE);
		}
		DrawTexturePro(player.player_texture, player.sourceRec, player.destRec, player.origin, player.rotation, WHITE);
		drawMeteor(meteor);
		for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
		{
			if (shoot[i].active) DrawCircleV(shoot[i].position, shoot[i].radius, WHITE);
		}

		DrawText(FormatText("%01i", points), (screenWidth / 2) - 20, screenHeight / 20, 30, LIGHTGRAY);
		if (firstStart && !defeatStatus)
		{
			DrawText("Press Space to Start", screenWidth / 2 - (MeasureText("Press Space to Start", 30) / 2), screenHeight / 4, 30, WHITE);
		}
		if (defeatStatus)
		{
			DrawText("You Lose!", screenWidth / 2 - (MeasureText("You Lose!", 30) / 2), screenHeight / 4, 30, WHITE);
		}
		if (pause)
		{
			DrawTexture(fond_black, 0, 0, WHITE);
			DrawTexture(asteroids, 0, 0, WHITE);
			if (menuButtonAnimationOn)
			{
				DrawTexture(menu, screenWidth / 2 - menu.width / 2, screenHeight / 2, WHITE);
			}
			else
			{
				DrawTexture(negativeMenu, screenWidth / 2 - negativeMenu.width / 2, screenHeight / 2, WHITE);
			}
			if (restartButtonAnimationOn)
			{
				DrawTexture(restart, screenWidth / 2 - exit.width / 2, screenHeight / 2 + restart.height + 5, WHITE);
			}
			else
			{
				DrawTexture(negativeRestart, screenWidth / 2 - exit.width / 2, screenHeight / 2 + restart.height + 5, WHITE);
			}
			if (exitButtonAnimationOn)
			{
				DrawTexture(exit, screenWidth / 2 - exit.width / 2, screenHeight / 2 + exit.height * 2 + 5, WHITE);
			}
			else
			{
				DrawTexture(negativeExit, screenWidth / 2 - exit.width / 2, screenHeight / 2 + exit.height * 2 + 5, WHITE);
			}
		}
	}
	void initMeteor(Meteor meteor[])
	{
		for (int i = 0; i < TOTAL_METEOR; i++)
		{
			meteor[i].x = GetRandomValue(1, screenWidth);
			meteor[i].y = GetRandomValue(1, screenHeight);
			while (meteor[i].y > screenHeight / 3 && meteor[i].y < screenHeight - screenHeight / 3)
			{
				meteor[i].y = GetRandomValue(1, screenHeight);
			}
			meteor[i].position = Vector2{ meteor[i].x, meteor[i].y };
			meteor[i].speed = Vector2{ SPEED_BALL_INIT, SPEED_BALL_INIT };
			meteor[i].radius = RADIUS_BALL;
			meteor[i].active = true;
			meteor[i].dir = (Direction)GetRandomValue(1, 8);
			meteor[i].sourceRec = { 0.0f,0.0f,(float)meteor[0].meteor_texture.width,(float)meteor[0].meteor_texture.height };
			meteor[i].destRec = { meteor[i].x,meteor[i].y,(float)meteor[0].meteor_texture.width,(float)meteor[0].meteor_texture.height };
			meteor[i].origin = { (float)meteor[0].meteor_texture.width / 2,(float)meteor[0].meteor_texture.height / 2 };

		}
	}
	static void drawMeteor(Meteor meteor[])
	{
		for (int i = 0; i < TOTAL_METEOR; i++)
		{
			DrawTexturePro(meteor[0].meteor_texture, meteor[i].sourceRec, meteor[i].destRec, meteor[i].origin, 0.0f, WHITE);
		}
	}
	static void checkColisionMeteor(Meteor meteor[])
	{
		//Colision bala-meteoro
		for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
		{
			if ((shoot[i].active))
			{
				for (int a = 0; a < TOTAL_METEOR; a++)
				{
					if (meteor[a].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, meteor[a].position, meteor[a].radius))
					{
						for (int x = 0; x < PLAYER_MAX_SHOOTS; x++)
						{
							shoot[x].active = false;
						}
						i = PLAYER_MAX_SHOOTS;
						points++;
						shoot[i].lifeSpawn = 0;
						instanceThisMeteor(meteor, a);

						if (music)
						{
							randomMusic = GetRandomValue(1, 4);
							switch (randomMusic) {
							case 1:
								PlaySound(fxWav);
								break;
							case 2:
								PlaySound(fxWav2);
								break;
							case 3:
								PlaySound(fxWav3);
								break;
							case 4:
								PlaySound(fxWav4);
								break;
							}
						}
					}
				}
			}
		}
		//---------------------------------------------------------
		//Colision meteoro-player
		for (int i = 0; i < TOTAL_METEOR; i++)
		{
			player.collider = Vector3{ player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight / 2.5f), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight / 2.5f), 12 };
			if (CheckCollisionCircles(Vector2{ player.collider.x, player.collider.y }, player.collider.z, meteor[i].position, meteor[i].radius) && meteor[i].active)
			{
				if (music)
				{
					randomMusic = GetRandomValue(1, 4);
					switch (randomMusic) {
					case 1:
						PlaySound(fxWav);
						break;
					case 2:
						PlaySound(fxWav2);
						break;
					case 3:
						PlaySound(fxWav3);
						break;
					case 4:
						PlaySound(fxWav4);
						break;
					}
				}
				defeat();
			}
		}
	}
	static void movMeteor(Meteor meteor[])
	{
		for (int i = 0; i < TOTAL_METEOR; i++)
		{
			switch (meteor[i].dir)
			{
			case Up:
				meteor[i].x -= velocity * GetFrameTime();
				break;
			case Right:
				meteor[i].y += velocity * GetFrameTime();
				break;
			case Left:
				meteor[i].y -= velocity * GetFrameTime();
				break;
			case Down:
				meteor[i].x += velocity * GetFrameTime();
				break;
			case UpRight:
				meteor[i].x -= velocity * GetFrameTime();
				meteor[i].y += velocity * GetFrameTime();
				break;
			case UpLeft:
				meteor[i].x -= velocity * GetFrameTime();
				meteor[i].y -= velocity * GetFrameTime();
				break;
			case DownRight:
				meteor[i].x += velocity * GetFrameTime();
				meteor[i].y += velocity * GetFrameTime();
				break;
			case DownLeft:
				meteor[i].x += velocity * GetFrameTime();
				meteor[i].y -= velocity * GetFrameTime();
				break;
			}
		}
	}
	static void instanceThisMeteor(Meteor meteor[], int thisMeteor)
	{
		Limits limit = (Limits)GetRandomValue(1, 4);
		switch (limit)
		{
		case LimitTop:
			meteor[thisMeteor].x = GetRandomValue(-RADIUS_BALL, screenWidth + RADIUS_BALL);
			meteor[thisMeteor].y = -RADIUS_BALL;
			break;
		case LimitDown:
			meteor[thisMeteor].x = GetRandomValue(-RADIUS_BALL, screenWidth + RADIUS_BALL);
			meteor[thisMeteor].y = screenHeight + RADIUS_BALL;
			break;
		case LimitRight:
			meteor[thisMeteor].x = screenWidth + RADIUS_BALL;
			meteor[thisMeteor].y = GetRandomValue(-RADIUS_BALL, screenHeight + RADIUS_BALL);
			break;
		case LimitLeft:
			meteor[thisMeteor].x = -RADIUS_BALL;
			meteor[thisMeteor].y = GetRandomValue(-RADIUS_BALL, screenHeight + RADIUS_BALL);
			break;
		}
		meteor[thisMeteor].dir = (Direction)GetRandomValue(1, 8);
	}
	static void initShoot(Shoot shoot[])
	{
		for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
		{
			shoot[i].position = Vector2{ 0, 0 };
			shoot[i].speed = Vector2{ 0, 0 };
			shoot[i].radius = 2;
			shoot[i].active = false;
			shoot[i].lifeSpawn = 0;
			shoot[i].color = WHITE;
		}
	}
	static void victory()
	{
		if (points >= MAX_POINT)
		{
			restartPlayer();
			firstStart = true;
			screen = WIN;
			initMeteor(meteor);
			points = INIT_SCORE;
			player.position = Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
			player.rotation = 0;
		}
	}
	static void defeat()
	{
		firstStart = true;
		defeatStatus = true;
		if (timeDefeat >= 2)
		{
			restartPlayer();
			defeatStatus = false;
			timeDefeat = 0;
			initMeteor(meteor);
			points = INIT_SCORE;
			player.position = Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
			player.rotation = 0;
			screen = DEFEAT;
		}
	}
	void CloseGameplay()
	{
		UnloadTexture(meteor[0].meteor_texture);
		UnloadTexture(player.player_texture);
		UnloadTexture(menu);
		UnloadTexture(negativeMenu);
		UnloadTexture(exit);
		UnloadTexture(negativeExit);
		UnloadTexture(asteroids);
		UnloadTexture(fond_black);
		UnloadTexture(boton_pause);
		UnloadTexture(negativePause);
		UnloadTexture(fond);
		UnloadTexture(asteroids);
		UnloadSound(fxWav);
		UnloadSound(fxWav2);
		UnloadSound(fxWav3);
		UnloadSound(fxWav4);
	}
	static void restartPlayer()
	{
		player.position = Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
		player.speed = Vector2{ 0, 0 };
		player.acceleration = { 0,0 };
		player.rotation = 0;
		player.sourceRec = { 0.0f,0.0f,(float)player.player_texture.width,(float)player.player_texture.height };
		player.destRec = { player.position.x,player.position.y,(float)player.player_texture.width,(float)player.player_texture.height };
		player.origin = { (float)player.player_texture.width / 2,(float)player.player_texture.height / 2 };
		player.collider = Vector3{ player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight / 2.5f), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight / 2.5f), 12 };
	}
}

