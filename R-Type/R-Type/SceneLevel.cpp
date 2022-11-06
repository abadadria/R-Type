#include <iostream>
#include <cmath>
#include <string>
#include <Windows.h>
#include <mmsystem.h>
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


void SceneLevel::load()
{
	Scene::init();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(0, 0), texProgram);

	spritesheetBeamStatus.loadFromFile("images/beamStatus.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBeamStatus = Sprite::createSprite(glm::ivec2(240, 32), glm::vec2(1, 1), &spritesheetBeamStatus, &texProgram);
	spriteBeamStatus->setPosition(posBeamStatus);

	spritesheetBeamStatusBar.loadFromFile("images/beamStatusBar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBeamStatusBar = Sprite::createSprite(glm::ivec2(230, 0), glm::vec2(1, 1), &spritesheetBeamStatusBar, &texProgram);
	spriteBeamStatusBar->setPosition(posBeamStatusBar);

	spritesheetAuxQuad.loadFromFile("images/auxQuad.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteAuxQuad = Sprite::createSprite(glm::ivec2(350, 250), glm::vec2(1, 1), &spritesheetAuxQuad, &texProgram);

	spritesheetBackHUDQuad.loadFromFile("images/backHUDQuad.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBackHUDQuad = Sprite::createSprite(glm::ivec2(640, 32), glm::vec2(1, 1), &spritesheetBackHUDQuad, &texProgram);
	spriteBackHUDQuad->setPosition(glm::vec2(0, 512));
}

void SceneLevel::init() {
	Scene::init();
	map->resetSpawnedEnemies();
	player = Player::getInstance();
	player->init(texProgram, map);
	player->setPosition(glm::vec2(INIT_PLAYER_X, INIT_PLAYER_Y));

	score = 0;
	lives = 3;
	playerDead = false;
	change = NO_CHANGE;

	text0 = new Text();
	if (!text0->init("fonts/dogica.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

	text1 = new Text();
	if (!text1->init("fonts/dogicapixelbold.ttf")) {
		cout << "Could not load font!!!" << endl;
	}

	// Clears all previous enemies and their bullets
	for (std::list<AutonomousEntity*>::iterator it = enemies.begin(); it != enemies.end();) {
		(*it)->kill();
		delete (*it);
		enemies.erase(it++);
	}
	// Spawn enemies before tileCol
	int initialTileCol = 21;
	int tileCol = getEnemySpawnColumn();
	for (int c = initialTileCol; c <= tileCol; ++c) {
		vector<pair<int, list<pair<int, int>>>> enemiesToSpawn = map->getEnemies(c);
		for (int i = 0; i < enemiesToSpawn.size(); ++i) {
			int row = enemiesToSpawn[i].first;
			list<pair<int, int>> list = enemiesToSpawn[i].second;
			for (pair<int, int> p : list) {
				AutonomousEntity* enemy;
				switch (p.first) {
					case 2:
						enemy = new RedPlane();
						break;
					default:
						enemy = nullptr;
				}
				enemy->init(texProgram, map, glm::ivec2(c * map->getTileSize(), row * map->getTileSize()), p.second);
				enemies.push_back(enemy);
			}
		}
	}

	mciSendString(TEXT("stop sounds/IntergalacticOdyssey.mp3"), NULL, 0, NULL);
	mciSendString(TEXT("play sounds/Chiptronical.mp3 repeat"), NULL, 0, NULL);
}

void SceneLevel::update(int deltaTime)
{
	Camera* cam = Camera::getInstance();
	glm::ivec2 posCamera = cam->getPos();
	if (!playerDead) {
		Scene::update(deltaTime);
		projection = camera->update();

		// Get new enemies to spawn
		int tileCol = getEnemySpawnColumn();
		vector<pair<int, list<pair<int, int>>>> enemiesToSpawn = map->getEnemies(tileCol);
		for (int i = 0; i < enemiesToSpawn.size(); ++i) {
			int row = enemiesToSpawn[i].first;
			list<pair<int, int>> list = enemiesToSpawn[i].second;
			for (pair<int, int> p : list) {
				AutonomousEntity* enemy;
				switch (p.first) {
					case 2:
						enemy = new RedPlane();
						break;
					default:
						enemy = nullptr;
				}
				enemy->init(texProgram, map, glm::ivec2(tileCol * map->getTileSize(), row * map->getTileSize()), p.second);
				enemies.push_back(enemy);
			}
		}

		// Update all entities
		player->update(deltaTime, this);
		for (std::list<AutonomousEntity*>::iterator it = enemies.begin(); it != enemies.end();) {
			int state = (*it)->getState();
			if (state == COMPLETELY_DEAD) {
				delete (*it);
				enemies.erase(it++);
			}
			else {
				(*it)->update(deltaTime, this);
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
		else if (Game::instance().getKey(13)) { // ENTER key
			change = RETRY;
		}
		else change = NO_CHANGE;
		if (lives == 0) change = GOTO_MENU;
	}
	
	if (player->getState() == COMPLETELY_DEAD) {
		// borrar la entidad de player
		playerDead = true;
	}
	else playerDead = false;
	
	spriteAuxQuad->setPosition(glm::ivec2(posCamera.x + SCREEN_WIDTH/2 - 175, posCamera.y + SCREEN_HEIGHT / 2 - 125));
	spriteBackHUDQuad->setPosition(glm::ivec2(posCamera.x, 512));
}

void SceneLevel::render()
{

	spriteBackground->render();
	spriteBackHUDQuad->render();

	Scene::render();
	map->render();


	if (playerDead) spriteAuxQuad->render();

	// Render HUD text
	text1->render("Lifes: ", posLifes, textSize, textColor);
	text0->render(std::to_string(lives), glm::ivec2(posLifes.x + 90, posLifes.y), textSize, textColor);
	text1->render("Score: ", posScore, textSize, textColor);
	text0->render(std::to_string(score), glm::ivec2(posScore.x + 90, posScore.y), textSize, textColor);
	text1->render("BEAM", posBeam, textSize, textColor);

	if (playerDead) {
		if (lives > 0) {
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

	// Render other elements
	Scene::render();
	player->render();
 	if (!playerDead) {
		// Render enemies
		for (AutonomousEntity* enemy : enemies) {
			enemy->render();
		}
	}

	// Render Beam charge bar
	Camera* cam = Camera::getInstance();
	glm::ivec2 posCamera = cam->getPos();
	spriteBeamStatus->setPosition(glm::vec2(posBeamStatus.x + posCamera.x, posBeamStatus.y));
	spriteBeamStatus->render();

	int size = player->getBeamCharge();
	// ensure max sixe of beam
	if (size > 70) size = 70;
	spriteBeamStatusBar = Sprite::createSprite(glm::ivec2((size * 230 / 70), 22), glm::vec2(1, 1), &spritesheetBeamStatusBar, &texProgram);
	spriteBeamStatusBar->setPosition(glm::vec2(posBeamStatusBar.x + posCamera.x, posBeamStatusBar.y));
	spriteBeamStatusBar->render();
	
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

int SceneLevel::getScore() const
{
	return score;
}

void SceneLevel::setScore(int newScore)
{
	score = newScore;
}

void SceneLevel::increaseScore(int score)
{
	this->score += score;
}

void SceneLevel::decreaseScore(int score)
{
	this->score -= score;
}

void SceneLevel::changeShowCollisionBlock() 
{
	bool showCollisionBlock = map->getShowCollisionBlock();
	map->setShowCollisionBlock(!showCollisionBlock);
}

vector<pair<string, string>> SceneLevel::getCollisions(Entity* entity)
{
	string type = entity->getType();

	vector<pair<string, string>> collisions;

	if (type != "Player") {
		if (player->collision(entity))
			collisions.push_back(make_pair(player->getType(), ""));
		pair<bool, string> bullet_collision = player->getBulletCollisions(entity);
		if (bullet_collision.first)
			collisions.push_back(make_pair(bullet_collision.second, ""));
	}
 		

	for (AutonomousEntity* enemy : enemies) {
		if (enemy->collision(entity))
			collisions.push_back(make_pair(enemy->getType(), ""));
		pair<bool, string> bullet_collision = enemy->getBulletCollisions(entity);
		if (bullet_collision.first)
			collisions.push_back(make_pair(bullet_collision.second, ""));
	}

	return collisions;
}

int SceneLevel::getEnemySpawnColumn() const
{
	Camera* cam = Camera::getInstance();
	glm::ivec2 camPos, camSize;
	camPos = cam->getPos();
	camSize = cam->getSize();
	int cameraRightLimit = camPos.x + camSize.x;
	return cameraRightLimit / map->getTileSize() + 1;
}

