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
#include "SilverRobot.h"
#include "Turret.h"
#include "DragonFly.h"
#include "FinalBoss.h"
#include "ForceCoin.h"
#include <map>

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

	//If it existed, delete it
	if (force != nullptr) {
		force->kill();
		delete force;
	}
	force = nullptr;

	// TODO Remove hardcoded coin
	PassiveEntity* coin = new ForceCoin();
	coin->init(texProgram, map);
	coin->setPosition(glm::ivec2(300.f, 200.f));
	coin->setMovementVector(glm::ivec2(0.f, 0.f));
	powerUps.push_back(coin);

	score = 0;
	lives = 3;
	playerDead = false;
	change = NO_CHANGE;
	checkpoint = 0;
	stateBoss = 0;

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
	// Clears all previous powerups
	for (std::list<PassiveEntity*>::iterator it = powerUps.begin(); it != powerUps.end();) {
		(*it)->kill();
		delete (*it);
		powerUps.erase(it++);
	}
	// Spawn enemies before tileCol
	int initialTileCol = 21;
	int tileCol = getEnemySpawnColumn();
	for (int c = initialTileCol; c <= tileCol; ++c) {
		vector<pair<int, list<std::map<string, int>>>> enemiesToSpawn = map->getEnemies(c);
		for (int i = 0; i < enemiesToSpawn.size(); ++i) {
			int row = enemiesToSpawn[i].first;
			list<std::map<string, int>> list = enemiesToSpawn[i].second;
			for (std::map<string, int> e : list) {
				AutonomousEntity* enemy;
				switch (e["enemyType"]) {
					case 2:
						enemy = new RedPlane();
						break;
					case 3:
						enemy = new SilverRobot();
						break;
					case 4:
						enemy = new Turret();
						break;
					case 5:
						enemy = new DragonFly();
						break;
					case 6:
						enemy = new FinalBoss();
						break;
					default:
						enemy = nullptr;
				}
				enemy->init(texProgram, map, glm::ivec2(c * map->getTileSize(), row * map->getTileSize()), e["extraInfo"], e["powerUp"]);
				enemies.push_back(enemy);
			}
		}
	}

	textColor = glm::vec4(1.f, 1.f, 1.f, 1);

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
		vector<pair<int, list<std::map<string, int>>>> enemiesToSpawn = map->getEnemies(tileCol);
		for (int i = 0; i < enemiesToSpawn.size(); ++i) {
			int row = enemiesToSpawn[i].first;
			list<std::map<string, int>> list = enemiesToSpawn[i].second;
			for (std::map<string, int> e : list) {
				AutonomousEntity* enemy;
				switch (e["enemyType"]) {
					case 2:
						enemy = new RedPlane();
						break;
					case 3:
						enemy = new SilverRobot();
						break;
					case 4:
						enemy = new Turret();
						break;
					case 5:
						enemy = new DragonFly();
						break;
					case 6:
						enemy = new FinalBoss();
						break;
					default:
						enemy = nullptr;
				}
				enemy->init(texProgram, map, glm::ivec2(tileCol * map->getTileSize(), row * map->getTileSize()), e["extraInfo"], e["powerUp"]);
				enemies.push_back(enemy);
			}
		}

		// Update all entities
		player->update(deltaTime, this);
		if (force != nullptr)
			force->update(deltaTime, this);
		// Update enemies
		for (std::list<AutonomousEntity*>::iterator it = enemies.begin(); it != enemies.end();) {
			int state = (*it)->getState();
			if (state == DEAD && (*it)->getDropPowerUp()) {
				(*it)->update(deltaTime, this);
				
				PassiveEntity* coin = new ForceCoin();
				coin->init(texProgram, map);

				// Center coin on the space where the enemy was
				glm::ivec2 enemyPos = (*it)->getPosition();
				glm::ivec2 enemySize = (*it)->getSize();
				glm::ivec2 coinSize = coin->getSize();
				glm::ivec2 coinPos = enemyPos + enemySize / 2 - coinSize / 2;
				coin->setPosition(coinPos);
				coin->setMovementVector(glm::ivec2(0.f, 0.f));
				powerUps.push_back(coin);

				++it;
			} 
			else if (state == COMPLETELY_DEAD)  {
				delete (*it);
				enemies.erase(it++);
			}
			else {
				(*it)->update(deltaTime, this);
				++it;
			}
		}
		// Update power ups
		for (std::list<PassiveEntity*>::iterator it = powerUps.begin(); it != powerUps.end();) {
			int state = (*it)->getState();
			if (state == COMPLETELY_DEAD) {
				delete (*it);
				powerUps.erase(it++);
			}
			else {
				(*it)->update(deltaTime, this);
				++it;
			}
		}
		change = NO_CHANGE;
	}
	else {
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

	if (posCamera.x >= 7505) {
		cam->setSpeed(glm::vec2(0,0));
		if (stateBoss != 2) stateBoss = 1;
	}
	else if (posCamera.x == 2350) {
		checkpoint = 2;
	}
	else if (posCamera.x == 4500) {
		checkpoint = 3;
	}
	else if (posCamera.x == 6600) {
		checkpoint = 4;
	}
	
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

	if (player->getCollisionsActive()) {
		textColor = glm::vec4(1.f, 1.f, 1.f, 1);
	}
	else {
		textColor = glm::vec4(1.f, 0.1, 0.1, 1);
	}
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

	// Check if boss defeated
	if (stateBoss == 1) { // Fighting the boss
		if (enemies.size() == 0)  // Boss dead
			stateBoss = 2;
	}
	else if (stateBoss == 2) {
		text1->render("YOU HAVE WON!!", glm::vec2(85, 210), 40, glm::vec4(1.f, 1.f, 1.f, 1));
		text1->render("CONGRATULATIONS PILOT", glm::vec2(30, 320), 30, glm::vec4(1.f, 1.f, 1.f, 1));
		text0->render("THANKS FOR PLAYING", glm::vec2(145, 360), 20, glm::vec4(1.f, 1.f, 1.f, 1));
		text0->render("PRESS [ESC] TO EXIT", glm::vec2(140, 400), 20, glm::vec4(1.f, 1.f, 1.f, 1));
	}

	// Render other elements
	Scene::render();
	player->render();
	if (force != nullptr && !playerDead)
		force->render();
 	if (!playerDead) {
		// Render enemies
		for (AutonomousEntity* enemy : enemies) {
			enemy->render();
		}
		for (PassiveEntity* p : powerUps) {
			p->render();
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
	delete spriteBeamStatusBar;
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
	if (score < 0) score = 0;
}

void SceneLevel::increaseScore(int score)
{
	this->score += score;
}

void SceneLevel::decreaseScore(int score)
{
	this->score -= score;
	if (score < 0) score = 0;
}

void SceneLevel::changeShowCollisionBlock() 
{
	bool showCollisionBlock = map->getShowCollisionBlock();
	map->setShowCollisionBlock(!showCollisionBlock);
}

void SceneLevel::changeCollisionsActivePlayer()
{
	player->changeCollisionsActive();
}

void SceneLevel::gotoCheckpoint(int checkpoint)
{
	if (!playerDead) {
		this->checkpoint = checkpoint;
		Camera* cam = Camera::getInstance();
		switch (this->checkpoint) {
		case 1:
			player->setPosition(glm::vec2(INIT_PLAYER_X, INIT_PLAYER_Y));
			camera->setPos(glm::vec2(0.f, 0.f));
			break;
		case 2:
			player->setPosition(glm::vec2(INIT_PLAYER_X + 2350, INIT_PLAYER_Y));
			camera->setPos(glm::vec2(2350, 0.f));
			break;
		case 3:
			player->setPosition(glm::vec2(INIT_PLAYER_X + 4500, INIT_PLAYER_Y));
			camera->setPos(glm::vec2(4500, 0.f));
			break;
		case 4:
			player->setPosition(glm::vec2(INIT_PLAYER_X + 6600, INIT_PLAYER_Y));
			camera->setPos(glm::vec2(6600, 0.f));
			break;
		}
	}
}

int SceneLevel::getCheckpoint()
{
	return checkpoint;
}

void SceneLevel::spawnForce()
{
	if (force == nullptr) {
		force = new Force();
		force->init(texProgram, map, player);
	}
	else {
		force->levelUp();
	}
}

void SceneLevel::doAllCollisions(Entity* entity)
{
	if (entity->getState() == ALIVE) {
		// Check collisions with player and bullets
		player->collision(entity, this);
		player->doBulletCollisions(entity, this);

		// Check collisions with Force and bullets
		if (force != nullptr) {
			force->collision(entity, this);
			force->doBulletCollisions(entity, this);
		}

		// Check collisions with enemies and bullets
		for (AutonomousEntity* enemy : enemies) {
			enemy->collision(entity, this);
			enemy->doBulletCollisions(entity, this);
		}

		// Check collisions with power ups
		for (PassiveEntity* powerUp : powerUps) {
			powerUp->collision(entity, this);
		}
	}
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

