#include <GL/glew.h>
#include <GL/glut.h>
#include <Windows.h>
#include <mmsystem.h>
#include "Game.h"


void Game::init()
{
	exit_game = false;
	state = MAIN_MENU;
	sceneLevel.load();
	sceneMenu.init();
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
		if (sceneLevel.getChange() == RETRY) {
			int lives = sceneLevel.getLives();
			int score = sceneLevel.getScore();
			int checkpoint = sceneLevel.getCheckpoint();
			sceneLevel.init();
			sceneLevel.gotoCheckpoint(checkpoint);
			sceneLevel.setLives(--lives);
			sceneLevel.setScore(score - 100);
			mciSendString(TEXT("play sounds/retry.wav"), NULL, 0, NULL);
		}
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
			glClearColor(0.f, 0.f, 0.f, 1.0f);
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
	int change;
	switch (key) {
		case 27: // Escape code
			if (state == PLAYING || state == INSTRUCTIONS || state == CREDITS) {
				change = sceneMenu.getItemSelected();
				sceneMenu.init();
				sceneMenu.setItemSelected(change);
				state = MAIN_MENU;
			}
			else {
				exit_game = true;
			}
			mciSendString(TEXT("play sounds/changeScreen.wav"), NULL, 0, NULL);
			break;
		case 13: // Enter code
			change = sceneMenu.getItemSelected();
			if (change == PLAY) {
				if (state == MAIN_MENU) {
					state = PLAYING;
					sceneLevel.init();
					mciSendString(TEXT("play sounds/retry.wav"), NULL, 0, NULL);
				}
			}
			else if (change == INST) {
				if (state == MAIN_MENU) {
					state = INSTRUCTIONS;
					mciSendString(TEXT("play sounds/changeScreen.wav"), NULL, 0, NULL);
				}
			}
			else if (change == CRED) {
				if (state == MAIN_MENU) {
					state = CREDITS;
					mciSendString(TEXT("play sounds/changeScreen.wav"), NULL, 0, NULL);
				}
			}
			else if (change == EXIT) {
				exit_game = true;
				mciSendString(TEXT("play sounds/changeScreen.wav"), NULL, 0, NULL);
			}
			break;
		case 'o':
			if (state == PLAYING) sceneLevel.changeShowCollisionBlock();
			break;
		case 'g':
			if (state == PLAYING) sceneLevel.changeCollisionsActivePlayer();
			break;
		case 'f':
			if (state == PLAYING) sceneLevel.spawnForce();
			break;
		case '1':
			if (state == PLAYING) {
				sceneLevel.init();
				sceneLevel.gotoCheckpoint(1);
			}
			break;
		case '2':
			if (state == PLAYING) {
				sceneLevel.init();
				sceneLevel.gotoCheckpoint(2);
			}
			break;
		case '3':
			if (state == PLAYING) {
				sceneLevel.init();
				sceneLevel.gotoCheckpoint(3);
			}
			break;
		case '4':
			if (state == PLAYING) {
				sceneLevel.init();
				sceneLevel.gotoCheckpoint(4);
			}
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





