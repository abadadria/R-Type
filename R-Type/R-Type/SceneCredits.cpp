#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneCredits.h"
#include "Game.h"



SceneCredits::SceneCredits()
{
	text0 = NULL;
	text1 = NULL;
	text2 = NULL;
}

SceneCredits::~SceneCredits()
{
	if (text0 != NULL)
		delete text0;
	if (text1 != NULL)
		delete text1;
	if (text2 != NULL)
		delete text2;
}


void SceneCredits::init()
{
	Scene::init();

	text0 = new Text();
	if (!text0->init("fonts/RetronoidItalic.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

	text1 = new Text();
	if (!text1->init("fonts/dogica.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

	text2 = new Text();
	if (!text2->init("fonts/dogicapixelbold.ttf")) {
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
	text0->render("BACK [ESC]", posBack, textBackSize, textBackColor);
	text0->render("CREDITS", posCred, textCredSize, textColor);

	text2->render("PROGRAMMERS", posElem, textElemSize, textElemColor);
	text1->render("ADRIA ABAD AND RAUL SAMPIETRO", posElem + glm::vec2(-110, 30), textElemSize - 5, textElemColor);

	text2->render("USED ASSETS", posElem + glm::vec2(0, 90), textElemSize, textElemColor);
	text1->render("FROM RETROGAMEZONE.CO.UK/RTYPE", posElem + glm::vec2(-120, 120), textElemSize - 5, textElemColor);

	text2->render("USED FONTS", posElem + glm::vec2(0, 180), textElemSize, textElemColor);
	text1->render("DOGICA AND RETRONOID", posElem + glm::vec2(-55, 210), textElemSize - 5, textElemColor);

	text2->render("BASED ON", posElem + glm::vec2(10, 270), textElemSize, textElemColor);
	text1->render("R-TYPE BY IREM", posElem + glm::vec2(-20, 300), textElemSize - 5, textElemColor);

	Scene::render();
}
