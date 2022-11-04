#include <iostream>
#include <cmath>
#include <string>
#include "SceneLevel.h"
#include "Game.h"
#include <GL/freeglut_std.h>
#include "PatternSin.h"
#include "RedPlane.h"

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
	AutonomousEntity* enemy = new RedPlane();
	enemy->init(texProgram, map, glm::ivec2(400, 240));
	enemies.push_back(enemy);
	
	score = 1000; // cambiar por 0, valor de prueba
	lives = 3;
	playerDead = false;

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

	spritesheetAuxQuad.loadFromFile("images/auxQuad.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteAuxQuad = Sprite::createSprite(glm::ivec2(350, 250), glm::vec2(1, 1), &spritesheetAuxQuad, &texProgram);
}

void SceneLevel::update(int deltaTime)
{
	if (!playerDead) {
		Scene::update(deltaTime);
		projection = camera->update();

		// Get new enemies to spawn
		Camera* cam = Camera::getInstance();
		glm::ivec2 camPos, camSize;
		camPos = cam->getPos();
		camSize = cam->getSize();
		int cameraRightLimit = camPos.x + camSize.x;
		int tileCol = cameraRightLimit / map->getTileSize();
		vector<pair<int, list<int>>> enemiesToSpawn = map->getEnemies(tileCol);
		for (int i = 0; i < enemiesToSpawn.size(); ++i) {
			int row = enemiesToSpawn[i].first;
			list<int> list = enemiesToSpawn[i].second;
			for (int e : list) {
				AutonomousEntity* enemy;
				switch (e) {
					case 2:
						enemy = new RedPlane();
						break;
					default:
						enemy = nullptr;
				}
				enemy->init(texProgram, map, glm::ivec2(tileCol * map->getTileSize(), row * map->getTileSize()));
				enemies.push_back(enemy);
			}
		}

		// Update enemies
		player->update(deltaTime);
		for (std::list<AutonomousEntity*>::iterator it = enemies.begin(); it != enemies.end();) {
			int state = (*it)->getState();
			if (state == COMPLETELY_DEAD) {
				delete (*it);
				enemies.erase(it++);
			}
			else {
				(*it)->update(deltaTime);
				++it;
			}
		}
		change = NO_CHANGE;
	}
	else {
		// render el spirte que diga retry o go back to menu
		// obtener que tecla se pulsa (como se hace en player)
		// cambiar estado a lo que corresponda GOTO_MENU o RETRY
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
		if (Game::instance().getKey(27)) change = GOTO_MENU; // ESC key
		else if (Game::instance().getKey(13)) change = RETRY; // ENTER key
		else change = NO_CHANGE;
		if (lives == 0) change = GOTO_MENU;
		
	}
	if (player->getState() == COMPLETELY_DEAD) playerDead = true;
	else playerDead = false;

	glm::ivec2 posCamera = camera->getPos();
	spriteAuxQuad->setPosition(glm::ivec2(posCamera.x + SCREEN_WIDTH/2 - 175, posCamera.y + SCREEN_HEIGHT / 2 - 125));
}

void SceneLevel::render()
{
	if (playerDead) spriteAuxQuad->render();

	// no necesitan update de la pos
	text1->render("Lifes: ", posLifes, textSize, textColor);
	text0->render(std::to_string(lives), glm::ivec2(posLifes.x + 90, posLifes.y), textSize, textColor);
	text1->render("Score: ", posScore, textSize, textColor);
	text0->render(std::to_string(score), glm::ivec2(posScore.x + 90, posScore.y), textSize, textColor);
	text1->render("BEAM", posBeam, textSize, textColor);

	if (playerDead) {
		if (lives > 1) {
			text1->render("DEAD!!", glm::vec2(267, 210), 20, textColor);
			text0->render("[ENTER] RETRY", glm::vec2(185, 270), 20, textColor);
			text0->render("[ESC] MAIN MENU", glm::vec2(165, 340), 20, textColor);
		}
		else {
			text1->render("GAME OVER", glm::vec2(235, 210), 20, textColor);
			text0->render("NO MORE LIVES", glm::vec2(190, 270), 20, textColor);
			text0->render("[ESC] MAIN MENU", glm::vec2(165, 340), 20, textColor);
		}
	}

	Scene::render();
	map->render();
	player->render();
	for (AutonomousEntity* enemy : enemies) {
		enemy->render();
	}

	Camera* cam = Camera::getInstance();
	glm::vec2 posCamera = cam->getPos();
	spriteBeamStatus->setPosition(glm::vec2(posBeamStatus.x + posCamera.x, posBeamStatus.y));
	spriteBeamStatus->render();

	int size = player->getBeamCharge();
	// ensure max sixe of beam
	if (size > 150) size = 150;
	spriteBeamStatusBar = Sprite::createSprite(glm::ivec2((size * 230 / 150), 22), glm::vec2(1, 1), &spritesheetBeamStatusBar, &texProgram);
	spriteBeamStatusBar->setPosition(glm::vec2(posBeamStatusBar.x + posCamera.x, posBeamStatusBar.y));
	spriteBeamStatusBar->render();

	// no se puede hacer antes del Scene::render
	
}

int SceneLevel::getChange()
{
	return change;
}

int SceneLevel::getLives()
{
	return lives;
}

void SceneLevel::setLives(int newLives)
{
	lives = newLives;
}

int SceneLevel::getScore()
{
	return score;
}

void SceneLevel::setScore(int newScore)
{
	score = newScore;
}

