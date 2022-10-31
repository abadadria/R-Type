#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneInstructions.h"
#include "Game.h"



SceneInstructions::SceneInstructions()
{
	text = NULL;
}

SceneInstructions::~SceneInstructions()
{
	if (text != NULL)
		delete text;
}


void SceneInstructions::init()
{
	Scene::init();

	text = new Text();
	if (!text->init("fonts/RetronoidItalic.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

}

void SceneInstructions::update(int deltaTime)
{
	Scene::update(deltaTime);

}

void SceneInstructions::render()
{
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	text->render("BACK [ESC]", posBack, textBackSize, textBackColor);
	text->render("INSTRUCTIONS:", posInst, textInstSize, textColor);
	Scene::render();
}
