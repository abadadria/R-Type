#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <mmsystem.h>
#include "SceneMenu.h"
#include "Game.h"
#include <GL/freeglut_std.h>

#define STILL 0
#define UP 1 
#define DOWN 2 


SceneMenu::SceneMenu()
{
	text = NULL;
}

SceneMenu::~SceneMenu()
{
	if (text != NULL)
		delete text;
}


void SceneMenu::init()
{
	Scene::init();

	spritesheetLogo.loadFromFile("images/logo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteLogo = Sprite::createSprite(sizeLogo, glm::vec2(1, 1), &spritesheetLogo, &texProgram);
	spriteLogo->setPosition(posLogo);

	text = new Text();
	if (!text->init("fonts/RetronoidItalic.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

	textSelected = PLAY;
	changeSelected = STILL;

	mciSendString(TEXT("play sounds/IntergalacticOdyssey.mp3 repeat"), NULL, 0, NULL);
}

void SceneMenu::update(int deltaTime)
{
	bool key_up = Game::instance().getSpecialKey(GLUT_KEY_UP);
	bool key_down = Game::instance().getSpecialKey(GLUT_KEY_DOWN);
	if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		changeSelected = UP;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		changeSelected = DOWN;
	}
	if (!key_up && !key_down && changeSelected != STILL) {
		switch (textSelected) {
			case PLAY:
				if (changeSelected == UP) textSelected = EXIT;
				if (changeSelected == DOWN) textSelected = INST;
				break;
			case INST:
				if (changeSelected == UP) textSelected = PLAY;
				if (changeSelected == DOWN) textSelected = CRED;
				break;
			case CRED:
				if (changeSelected == UP) textSelected = INST;
				if (changeSelected == DOWN) textSelected = EXIT;
				break;
			case EXIT:
				if (changeSelected == UP) textSelected = CRED;
				if (changeSelected == DOWN) textSelected = PLAY;
				break;
		}
		changeSelected = STILL;
	}
	
	Scene::update(deltaTime);
}

void SceneMenu::render()
{
	spriteBackground->render();

	//PLAY
	if (textSelected == PLAY) text->render("PLAY", posPlay, textSize, selectedTextColor);
	else text->render("PLAY", posPlay, textSize, textColor);

	//INSTRUCTIONS
	if (textSelected == INST) text->render("INSTRUCTIONS", posInst, textSize, selectedTextColor);
	else text->render("INSTRUCTIONS", posInst, textSize, textColor);

	//CREDITS
	if (textSelected == CRED) text->render("CREDITS", posCred, textSize, selectedTextColor);
	else text->render("CREDITS", posCred, textSize, textColor);

	//EXIT
	if (textSelected == EXIT) text->render("EXIT", posExit, textSize, selectedTextColor);
	else text->render("EXIT", posExit, textSize, textColor);


	Scene::render();
	spriteLogo->render();
}

int SceneMenu::getItemSelected()
{
	return textSelected;
}

void SceneMenu::setItemSelected(int newSelected)
{
	textSelected = newSelected;
}

