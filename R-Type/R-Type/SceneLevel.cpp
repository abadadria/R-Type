#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneLevel.h"
#include "Game.h"

#define INIT_PLAYER_X 16
#define INIT_PLAYER_Y 240


SceneLevel::SceneLevel()
{
	map = NULL;
	player = NULL;
}

SceneLevel::~SceneLevel()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}


void SceneLevel::init()
{
	Scene::init();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(0, 0), texProgram);
	player = new Player();
	player->init(texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X, INIT_PLAYER_Y));
	player->setTileMap(map);
}

void SceneLevel::update(int deltaTime)
{
	Scene::update(deltaTime);
	cameraPos.x += 1.f;
	projection = glm::ortho(cameraPos.x, cameraPos.x + cameraSize.x, cameraPos.y + cameraSize.y, cameraPos.y);
	player->update(deltaTime, cameraPos, cameraSize);
}

void SceneLevel::render()
{
	Scene::render();

	map->render();
	player->render();
}

