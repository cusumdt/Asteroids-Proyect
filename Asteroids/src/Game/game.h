#ifndef GAME_H
#define GAME_H
namespace GameInit
{
	enum Screen
	{
		GAME,
		MENU,
		WIN,
		CREDITS,
		DEFEAT
	};
	extern Screen screen;
	extern bool music;
	//---------------------------------------------
	void LoadScreen();
	//---------------------------------------------
}
#endif // !GAME_H


