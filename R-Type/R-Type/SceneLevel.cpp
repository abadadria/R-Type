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

	spritesheetBeamStatus.loadFromFile("images/beamStatus.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBeamStatus = Sprite::createSprite(glm::ivec2(320, 32), glm::vec2(1, 1), &spritesheetBeamStatus, &texProgram);
	spriteBeamStatus->setPosition(posBeamStatus);

	spritesheetBeamStatusBar.loadFromFile("images/beamStatusBar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBeamStatusBar = Sprite::createSprite(glm::ivec2(310, 22), glm::vec2(1, 1), &spritesheetBeamStatusBar, &texProgram);
	spriteBeamStatusBar->setPosition(posBeamStatusBar);
}

void SceneLevel::update(int deltaTime)
{
	Scene::update(deltaTime);
	projection = camera->update();
	player->update(deltaTime);
}

void SceneLevel::render()
{
	// no necesitan update de la pos
	text0->render("Lives: ", posLives, textSize, textColor);
	text0->render("Score: ", posScore, textSize, textColor);
	text0->render("BEAM", posBeam, textSize, textColor);

	Scene::render();

	map->render();
	player->render();

	Camera* cam = Camera::getInstance();
	glm::vec2 posCamera = cam->getPos();
	spriteBeamStatus->setPosition(glm::vec2(posBeamStatus.x + posCamera.x, posBeamStatus.y));
	spriteBeamStatusBar->setPosition(glm::vec2(posBeamStatusBar.x + posCamera.x, posBeamStatusBar.y));

	spriteBeamStatus->render();
	spriteBeamStatusBar->render();

	// render all the sprites
	// update the position acording to its own position plus the camera movement
}

