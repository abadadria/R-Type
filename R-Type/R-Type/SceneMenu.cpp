#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneMenu.h"
#include "Game.h"



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
	if (!text->init("fonts/arcade.ttf")) {
		cout << "Could not load font!!!" << endl;
	}
}

void SceneMenu::update(int deltaTime)
{
	Scene::update(deltaTime);

}

void SceneMenu::render()
{
	text->render("Porfin mecagoendios", glm::vec2(300, 300), 24, glm::vec4(0, 1, 0, 1));
	
	Scene::render();
	spriteLogo->render();
}

