#include <iostream>
#include <cmath>
#include "SceneLevel.h"
#include "Game.h"

#define INIT_PLAYER_X 16
#define INIT_PLAYER_Y 240


SceneLevel::SceneLevel()
{
	map = NULL;
	player = NULL;
	text0 = NULL;
}

SceneLevel::~SceneLevel()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (text0 != NULL)
		delete text0;
}


void SceneLevel::init()
{
	Scene::init();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(0, 0), texProgram);
	player = new Player();
	player->init(texProgram, map);
	player->setPosition(glm::vec2(INIT_PLAYER_X, INIT_PLAYER_Y));
	score = 10000; // cambiar por 0, valor de prueba
	lives = 3;

	text0 = new Text();
	if (!text0->init("fonts/dogica.ttf")) {
		cout << "Could not load font!!!" << endl;
	}
}

void SceneLevel::update(int deltaTime)
{
	Scene::update(deltaTime);
	projection = camera->update();
	player->update(deltaTime);
	// update the position of all the sprites
}

void SceneLevel::render()
{
	Scene::render();

	map->render();
	player->render();
}

