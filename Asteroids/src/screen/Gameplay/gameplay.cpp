#include "Game\game.h"

#include "raylib.h"

#include "gameplay.h"
#include "Logic\mov_ship.h"
#include <ctime>
#include <iostream>
//#define MUSIC_ON
namespace GameInit
{
	Screen screen = MENU; 
	namespace Gameplay
	{
		enum Direction 
		{
			Up=1,
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
			float x;
			float y;
			Vector2 position;
			Vector2 speed;
			int radius;
			bool active;
			Direction dir;
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

	
		static void initMeteor(Meteor meteor[]);
		static void drawMeteor(Meteor meteor[]);
		static void checkColisionMeteor(Meteor meteor[]);
		static void movMeteor(Meteor meteor[]);
		static void instanceThisMeteor(Meteor meteor[], int thisMeteor);
		static void initShoot(Shoot shoot[]);
		static void victory();
		static void defeat();
		// Initialization
		//-------------------------------------------- Statics
		int screenWidth = 1600;
		int screenHeight = 900;
		static int checkGame = 1;
		static const int TOTAL_METEOR = 10;
		static Rectangle box2;
		static Meteor meteor[TOTAL_METEOR];
		static short int INIT_VELOCITY = 400;
		static short int randomMusic = 0;
		static const short int MAX_POINT = 1;
		static const short int HEIGHT_BOX = (screenHeight /15);
		static const short int WIDTH_BOX = (screenWidth / 25);
		static const short int RADIUS_BALL = (screenWidth / 45);
		static const short int SPEED_BALL_INIT = 0;
		static const short int MOVE_BOX = 400;
		static const short int INIT_SCORE = 0;
		static const short int LIMIT_TOP = 10;
		static const short int EXTRA_VELOCITY = 20;
		static const short int PLAYER_MAX_SHOOTS = 10;
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
		//--------------------------------------------
	
		bool left = false;
		bool right = false;
		bool firstInit = true;
		//--------------------------------------------
		void initGame() {

			fxWav = LoadSound("res/Blip_Select.wav");
			fxWav2= LoadSound("res/Blip_Select2.wav");
			fxWav3= LoadSound("res/Blip_Select3.wav");
			fxWav4 = LoadSound("res/Blip_Select4.wav");

			velocity = INIT_VELOCITY;
			//--------------------------------
			shipHeight = (PLAYER_BASE_SIZE / 2) / tanf(20 * DEG2RAD);
			player.position = Vector2 { (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
			player.speed = Vector2 { 0, 0 };
			player.acceleration = 0;
			player.rotation = 0;
			player.collider = Vector3 { player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight / 2.5f), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight / 2.5f), 12 };
			player.color = LIGHTGRAY;
			//--------------------------------
			initMeteor(meteor);
			initShoot(shoot);
			
		}

		
		void updateGame()
		{
			victory();
			SetExitKey(0);
			Logic_ship::mov_ship();
			if (IsKeyDown(KEY_M))
			{
				screen = MENU;
				initMeteor(meteor);
				points = INIT_SCORE;
				player.position = Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
				player.rotation = 0;
			}
			//---------------------------------------------------------
			//Meteor Movement
			movMeteor(meteor);
			//---------------------------------------------------------
			//Bordes pantalla
			for (int i = 0; i < TOTAL_METEOR; i++)
			{
				if (meteor[i].y <= (LIMIT_TOP - RADIUS_BALL *4) ||
					meteor[i].y >= (screenHeight + RADIUS_BALL * 4) ||
					meteor[i].x >= (screenWidth + RADIUS_BALL * 4) ||
					meteor[i].x <= (0 - RADIUS_BALL * 4))
				{
					instanceThisMeteor(meteor, i);
				}
		
			}
			//--------------------------------------------------------
			//Colision barras/pelota
			checkColisionMeteor(meteor);
			for (int i = 0; i < TOTAL_METEOR; i++)
			{
				meteor[i].position = Vector2{ meteor[i].x, meteor[i].y };
			}
			//-------------------------------------------------------
			if (IsKeyPressed(KEY_SPACE))
			{
				for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
				{
					if (!shoot[i].active)
					{
						shoot[i].position = Vector2 { player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight) };
						shoot[i].active = true;
						shoot[i].speed.x = 1.5*sin(player.rotation*DEG2RAD)*PLAYER_SPEED;
						shoot[i].speed.y = 1.5*cos(player.rotation*DEG2RAD)*PLAYER_SPEED;
						shoot[i].rotation = player.rotation;
					}
				}
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
						shoot[i].position = Vector2 { 0, 0 };
						shoot[i].speed = Vector2 { 0, 0 };
						shoot[i].lifeSpawn = 0;
						shoot[i].active = false;
					}
				}
			}

		
		}
		void DrawGame()
		{
			Vector2 v1 = { player.position.x + sinf(player.rotation*DEG2RAD)*(shipHeight), player.position.y - cosf(player.rotation*DEG2RAD)*(shipHeight) };
			Vector2 v2 = { player.position.x - cosf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE / 2), player.position.y - sinf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE / 2) };
			Vector2 v3 = { player.position.x + cosf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE / 2), player.position.y + sinf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE / 2) };
			DrawTriangle(v1, v2, v3, MAROON);
			drawMeteor(meteor);
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
			{
				if (shoot[i].active) DrawCircleV(shoot[i].position, shoot[i].radius, BLACK);
			}

			DrawText(FormatText("%01i", points), (screenWidth / 2) - 20, screenHeight / 20, 30, LIGHTGRAY);

			DrawText("PRESS M FOR RETURN TO THE MENU",	screenWidth / 2 - (MeasureText("PRESS M FOR RETURN TO THE MENU",15) / 2), screenHeight - screenHeight / 20 , 15, BLACK);
		}
		void initMeteor(Meteor meteor[])
		{
			for (int i = 0; i < TOTAL_METEOR; i++)
			{
				meteor[i].x = GetRandomValue(1, screenWidth);
				meteor[i].y = GetRandomValue(1, screenHeight);
				meteor[i].position = Vector2{ meteor[i].x, meteor[i].y };
				meteor[i].speed = Vector2{ SPEED_BALL_INIT, SPEED_BALL_INIT };
				meteor[i].radius = RADIUS_BALL;
				meteor[i].active = true;
				meteor[i].dir = (Direction)GetRandomValue(1, 8);
			}
		}
		static void drawMeteor(Meteor meteor[]) 
		{
			for (int i = 0; i < TOTAL_METEOR; i++)
			{
				DrawCircleV(meteor[i].position, meteor[i].radius, MAROON);
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
				player.collider = Vector3 { player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight / 2.5f), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight / 2.5f), 12 };
				if (CheckCollisionCircles(Vector2 { player.collider.x, player.collider.y }, player.collider.z, meteor[i].position, meteor[i].radius) && meteor[i].active) 
				{
					instanceThisMeteor(meteor, i);
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
				meteor[thisMeteor].x = screenWidth+RADIUS_BALL;
				meteor[thisMeteor].y = GetRandomValue(-RADIUS_BALL, screenHeight + RADIUS_BALL);
				break;
			case LimitLeft:
				meteor[thisMeteor].x = - RADIUS_BALL;
				meteor[thisMeteor].y = GetRandomValue(-RADIUS_BALL, screenHeight + RADIUS_BALL);
				break;
			}
			meteor[thisMeteor].dir = (Direction)GetRandomValue(1, 8);
		}
		static void initShoot(Shoot shoot[]) 
		{
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
			{
				shoot[i].position = Vector2 { 0, 0 };
				shoot[i].speed = Vector2 { 0, 0 };
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
				screen = WIN;
				initMeteor(meteor);
				points = INIT_SCORE;
				player.position = Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
				player.rotation = 0;
			}
		}
		static void defeat()
		{
				screen = DEFEAT;
				initMeteor(meteor);
				points = INIT_SCORE;
				player.position = Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
				player.rotation = 0;
			
		}
	}

}

