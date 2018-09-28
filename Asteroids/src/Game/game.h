#ifndef GAME_H
#define GAME_H
namespace GameInit
{
	enum Screen
	{
		GAME,
		MENU,
		WIN,
		CREDITS
	};
	extern Screen screen;

	//---------------------------------------------
	void LoadScreen();
	//---------------------------------------------
}
#endif // !GAME_H


