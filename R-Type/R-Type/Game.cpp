#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	exit_game = false;
	state = MAIN_MENU;
	sceneMenu.init();
	sceneLevel.init();
	sceneInstructions.init();
	sceneCredits.init();
}

bool Game::update(int deltaTime)
{
	switch (state) {
	case MAIN_MENU:
		sceneMenu.update(deltaTime);
		break;

	case PLAYING:
		sceneLevel.update(deltaTime);
		break;

	case INSTRUCTIONS:
		sceneInstructions.update(deltaTime);
		break;

	case CREDITS:
		sceneCredits.update(deltaTime);
		break;
	}
	return exit_game;

}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (state) {
		case MAIN_MENU:
			sceneMenu.render();
			break;

		case PLAYING:
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			sceneLevel.render();
			break;

		case INSTRUCTIONS:
			sceneInstructions.render();
			break;

		case CREDITS:
			sceneCredits.render();
			break;
	}
}

void Game::keyPressed(int key)
{
	switch (key) {
		case 27: // Escape code
			if (state == PLAYING || state == INSTRUCTIONS || state == CREDITS)
				state = MAIN_MENU;
			else
				exit_game = true;
			break;
		// TODO cambiar esta logica para que coja el valor del SceneMenu y haga lo que corresponda
		case 13: // Enter code
			int change = sceneMenu.getItemSelected();
			if (change == 0) {
				if (state == MAIN_MENU) state = PLAYING;
			}
			else if (change == 1) {
				if (state == MAIN_MENU) state = INSTRUCTIONS;
			}
			else if (change == 2) {
				if (state == MAIN_MENU) state = CREDITS;
			}
			else if (change == 3) exit_game = true;
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





