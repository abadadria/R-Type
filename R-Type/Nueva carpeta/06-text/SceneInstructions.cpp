#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneInstructions.h"
#include "Game.h"



SceneInstructions::SceneInstructions()
{

}

SceneInstructions::~SceneInstructions()
{

}


void SceneInstructions::init()
{
	Scene::init();

}

void SceneInstructions::update(int deltaTime)
{
	Scene::update(deltaTime);

}

void SceneInstructions::render()
{
	Scene::render();
	glClearColor(0.3f, 0.3f, 1.f, 1.0f);
}
