#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneCredits.h"
#include "Game.h"



SceneCredits::SceneCredits()
{
	text = NULL;
}

SceneCredits::~SceneCredits()
{
	if (text != NULL)
		delete text;
}


void SceneCredits::init()
{
	Scene::init();

	text = new Text();
	if (!text->init("fonts/RetronoidItalic.ttf")) {
		cout << "Could not load font!!!" << endl;
	}
}

void SceneCredits::update(int deltaTime)
{
	Scene::update(deltaTime);

}

void SceneCredits::render()
{
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	text->render("BACK [ESC]", posBack, textBackSize, textBackColor);
	text->render("CREDITS", posCred, textCredSize, textColor);
	Scene::render();
}
