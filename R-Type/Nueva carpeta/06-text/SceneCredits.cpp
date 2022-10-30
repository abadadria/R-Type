#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneCredits.h"
#include "Game.h"



SceneCredits::SceneCredits()
{

}

SceneCredits::~SceneCredits()
{

}


void SceneCredits::init()
{
	Scene::init();

}

void SceneCredits::update(int deltaTime)
{
	Scene::update(deltaTime);

}

void SceneCredits::render()
{
	Scene::render();
	glClearColor(0.3f, 1.f, 0.3f, 1.0f);
}
