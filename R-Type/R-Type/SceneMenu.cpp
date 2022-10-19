#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneMenu.h"
#include "Game.h"



SceneMenu::SceneMenu()
{
	
}

SceneMenu::~SceneMenu()
{

}


void SceneMenu::init()
{
	Scene::init();

	spritesheetLogo.loadFromFile("images/logo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteLogo = Sprite::createSprite(sizeLogo, glm::vec2(1, 1), &spritesheetLogo, &texProgram);
	spriteLogo->setPosition(posLogo);

	//text->init("fonts/arcade.ttf");
}

void SceneMenu::update(int deltaTime)
{
	Scene::update(deltaTime);

}

void SceneMenu::render()
{
	spriteLogo->render();
	Scene::render();
	
}

