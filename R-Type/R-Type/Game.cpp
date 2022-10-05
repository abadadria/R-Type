#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	exit_game = false;
	state = MAIN_MENU;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
}

bool Game::update(int deltaTime)
{
	if (state == PLAYING) 
		scene.update(deltaTime, true);
	else 
		scene.update(deltaTime, false);
	return exit_game;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (state) {
		case MAIN_MENU:
			//render lo que toca
			glClearColor(1.f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			break;

		case PLAYING:
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			scene.render();
			break;

		case INSTRUCTIONS:
			// render lo que toca
			glClearColor(0.3f, 1.f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			break;

		case CREDITS:
			//render lo que toca
			glClearColor(0.3f, 0.3f, 1.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		case 13: // Enter code
			if (state == MAIN_MENU)
				state = PLAYING;
			break;
		case 'i':
			if (state == MAIN_MENU)
				state = INSTRUCTIONS;
			break;
		case 'c':
			if (state == MAIN_MENU)
				state = CREDITS;
			break;
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





