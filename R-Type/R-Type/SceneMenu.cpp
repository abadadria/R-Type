#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
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
	//Paint all of them as equal
	text->render("PLAY", glm::vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 40, glm::vec4(0, 0.6, 0.6, 1));
	text->render("INSTRUCTIONS", glm::vec2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 60), 40, glm::vec4(0, 0.6, 0.6, 1));
	text->render("CREDITS", glm::vec2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 120), 40, glm::vec4(0, 0.6, 0.6, 1));
	text->render("EXIT", glm::vec2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 180), 40, glm::vec4(0, 0.6, 0.6, 1));

	//Repaint the one selected
	switch (textSelected) {
	case PLAY:
		text->render("PLAY", glm::vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 40, glm::vec4(0.5, 0.6, 0.6, 1));
		break;
	case INST:
		text->render("INSTRUCTIONS", glm::vec2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 60), 40, glm::vec4(0.5, 0.6, 0.6, 1));
		break;
	case CRED:
		text->render("CREDITS", glm::vec2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 120), 40, glm::vec4(0.5, 0.6, 0.6, 1));
		break;
	case EXIT:
		text->render("EXIT", glm::vec2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 180), 40, glm::vec4(0.5, 0.6, 0.6, 1));
		break;
	}

	Scene::render();
	spriteLogo->render();
}

