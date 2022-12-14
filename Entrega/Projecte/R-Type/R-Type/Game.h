#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "SceneLevel.h"
#include "SceneMenu.h"
#include "SceneCredits.h"
#include "SceneInstructions.h"


#define SCREEN_WIDTH 640
//#define SCREEN_HEIGHT 512
#define SCREEN_HEIGHT 544

#define MAIN_MENU 0
#define PLAYING 1
#define INSTRUCTIONS 2
#define CREDITS 3


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	/*
		state = 0 -> Main Menu
		state = 1 -> Playing status
		state = 2 -> Instructions
		state = 3 -> Credits
	*/
	bool exit_game;
	int state;								// State of the game
	SceneLevel sceneLevel;					// SceneLevel to render
	SceneMenu sceneMenu;					// SceneMenu to render
	SceneCredits sceneCredits;				// SceneCredits to render
	SceneInstructions sceneInstructions;	// SceneInstructions to render
	// MainMenu main_menu;
	// Instructions instructions;
	// Credits credits;
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time

};


#endif // _GAME_INCLUDE


