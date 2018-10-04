#ifndef GAMEPLAY_H
#define GAMEPLAY_H
namespace GameInit
{
	namespace Gameplay
	{
		extern bool firstInit;
		extern int screenWidth;
		extern int screenHeight;
		extern bool left;
		extern bool right;
		void initGame();
		void updateGame();
		void DrawGame();
	}
}
#endif