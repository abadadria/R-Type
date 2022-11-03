#include <iostream>
#include <cmath>
#include <string>
#include "SceneLevel.h"
#include "Game.h"

#define INIT_PLAYER_X 16
#define INIT_PLAYER_Y 240


SceneLevel::SceneLevel()
{
	map = NULL;
	player = NULL;
	text0 = NULL;
	text1 = NULL;
}

SceneLevel::~SceneLevel()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (text0 != NULL)
		delete text0;
	if (text1 != NULL)
		delete text1;
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

	text1 = new Text();
	if (!text1->init("fonts/dogicapixelbold.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

	spritesheetBeamStatus.loadFromFile("images/beamStatus.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBeamStatus = Sprite::createSprite(glm::ivec2(240, 32), glm::vec2(1, 1), &spritesheetBeamStatus, &texProgram);
	spriteBeamStatus->setPosition(posBeamStatus);

	spritesheetBeamStatusBar.loadFromFile("images/beamStatusBar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBeamStatusBar = Sprite::createSprite(glm::ivec2(230, 0), glm::vec2(1, 1), &spritesheetBeamStatusBar, &texProgram);
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
	text1->render("Lifes: ", posLifes, textSize, textColor);
	text0->render(std::to_string(lives), glm::ivec2(posLifes.x + 90, posLifes.y), textSize, textColor);
	text1->render("Score: ", posScore, textSize, textColor);
	text0->render(std::to_string(score), glm::ivec2(posScore.x + 90, posScore.y), textSize, textColor);
	text1->render("BEAM", posBeam, textSize, textColor);

	Scene::render();

	map->render();
	player->render();

	Camera* cam = Camera::getInstance();
	glm::vec2 posCamera = cam->getPos();
	spriteBeamStatus->setPosition(glm::vec2(posBeamStatus.x + posCamera.x, posBeamStatus.y));
	spriteBeamStatus->render();

	int size = player->getBeamCharge();
	// ensure max sixe of beam plus dont show if basic shot
	if (size > 150) size = 150;
	spriteBeamStatusBar = Sprite::createSprite(glm::ivec2((size * 230 / 150), 22), glm::vec2(1, 1), &spritesheetBeamStatusBar, &texProgram);
	spriteBeamStatusBar->setPosition(glm::vec2(posBeamStatusBar.x + posCamera.x, posBeamStatusBar.y));
	spriteBeamStatusBar->render();

	// render all the sprites
	// update the position acording to its own position plus the camera movement
}

