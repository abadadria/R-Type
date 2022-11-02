#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneInstructions.h"
#include "Game.h"



SceneInstructions::SceneInstructions()
{
	text0 = NULL;
	text1 = NULL;
}

SceneInstructions::~SceneInstructions()
{
	if (text0 != NULL)
		delete text0;
	if (text1 != NULL)
		delete text1;
}


void SceneInstructions::init()
{
	Scene::init();

	text0 = new Text();
	if (!text0->init("fonts/Retronoid.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

	text1 = new Text();
	if (!text1->init("fonts/dogica.ttf")) {
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
	text0->render("BACK [ESC]", posBack, textBackSize, textBackColor);
	text0->render("INSTRUCTIONS:", posInst, textInstSize, textColor);

	text1->render("-[UP_ARROW]: Move player to the top", posElem, textElemSize, textElemColor);
	text1->render("-[DOWN_ARROW]: Move player to the bottom", posElem + glm::vec2(0, 30), textElemSize, textElemColor);
	text1->render("-[LEFT_ARROW]: Move player to the left", posElem + glm::vec2(0, 60), textElemSize, textElemColor);
	text1->render("-[RIGHT_ARROW]: Move playe to the right", posElem + glm::vec2(0, 90), textElemSize, textElemColor);
	text1->render("-[SPACE_BAR]: Shoot normal shot", posElem + glm::vec2(0, 120), textElemSize, textElemColor);
	text1->render("-[SPACE_BAR](HOLD): Shoot special shot", posElem + glm::vec2(0, 150), textElemSize, textElemColor);
	text1->render("-[ESC]: Go back", posElem + glm::vec2(0, 180), textElemSize, textElemColor);
	text1->render("-[G]: Activate invulnerability", posElem + glm::vec2(0, 210), textElemSize, textElemColor);
	text1->render("-[F]: Activate Force", posElem + glm::vec2(0, 240), textElemSize, textElemColor);
	text1->render("-[1..3]: Skip levels", posElem + glm::vec2(0, 270), textElemSize, textElemColor);

	Scene::render();
}
 