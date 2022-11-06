#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <Windows.h>
#include <mmsystem.h>
#include <map>

#include "Player.h"
#include "Game.h"
#include "SpriteSpaceship.h"
#include "SpaceshipBullet.h"
#include "SpaceshipBeam.h"


enum PlayerAnims
{
	STAND, MOVE_UP, MOVE_DOWN, GO_BACK
};

Player* Player::instance{ nullptr };

Player::Player() {}

/*
Player::~Player() {
	delete instance;
}
*/
Player* Player::getInstance() {
	if (instance == nullptr) {
		instance = new Player();
	}
	return instance;
}

void Player::init(ShaderProgram &shaderProgram, TileMap* tileMap)
{
	ShootingEntity::init(shaderProgram, tileMap);
	entitySize = glm::ivec2(64, 32);
	spritesheet.loadFromFile("images/spaceship.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = SpriteSpaceship::createSpriteSpaceship(entitySize, glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
		
		int keyframesPerSec = 12;

		sprite->setAnimationSpeed(STAND, keyframesPerSec);
		sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));

		sprite->setAnimationSpeed(MOVE_UP, keyframesPerSec);
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.5f, 0.5f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.25f, 0.0f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.5f, 0.0f));

		sprite->setAnimationSpeed(MOVE_DOWN, keyframesPerSec);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.5f, 0.5f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25f, 0.0f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.5f, 0.0f));

		sprite->setAnimationSpeed(GO_BACK, keyframesPerSec);
		sprite->addKeyframe(GO_BACK, glm::vec2(0.5f, 0.5f));
		sprite->addKeyframe(GO_BACK, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(GO_BACK, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(GO_BACK, glm::vec2(0.25f, 0.0f));
		sprite->addKeyframe(GO_BACK, glm::vec2(0.5f, 0.0f));
	
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));

	beamCharger = 0;
	resetBeamCharge = true;
	state = ALIVE;
	collisionsActive = true;;
}

void Player::render() {
	if (beamCharger > 20) {
		spriteBeamCharge->render();
	}
	else if (resetBeamCharge) {
		spritesheetBeamCharge.loadFromFile("images/beamCharge.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spriteBeamCharge = Sprite::createSprite(glm::ivec2(33, 32), glm::vec2(0.125, 1), &spritesheetBeamCharge, texProgram);
		spriteBeamCharge->setNumberAnimations(1);
			
			int keyframesPerSec = 10;
			spriteBeamCharge->setAnimationSpeed(0, keyframesPerSec);
			spriteBeamCharge->setAnimationLooping(0, true);
			for (int i = 0.f; i < 8; i += 1)
				spriteBeamCharge->addKeyframe(0, glm::vec2(0.125f * float(i), 0.f));

		spriteBeamCharge->changeAnimation(0);
		resetBeamCharge = false;
		
	}
	// if charging beam, render la cosilla esa
	ShootingEntity::render();
}

string Player::getType() const
{
	return "Player";
}

int Player::getBeamCharge()
{
	return beamCharger;
}

void Player::changeCollisionsActive()
{
	collisionsActive = !collisionsActive;
}

bool Player::getCollisionsActive()
{
	return collisionsActive;
}

void Player::update(int deltaTime, SceneLevel* scene)
{
	ShootingEntity::update(deltaTime, scene);
	if (state == ALIVE) {
		// Shooting and Beam
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
		if (Game::instance().getKey(' ')) {
			beamCharger += 1;
			spriteBeamCharge->update(deltaTime);
			spriteBeamCharge->setPosition(glm::ivec2(posEntity.x + 65, posEntity.y + 5));
		}
		else if (beamCharger != 0) {
			glm::ivec2 posShoot(posEntity.x, posEntity.y);
			if (beamCharger < 20) { // basic shoot
				shoot(0);
			}
			else {
				if (beamCharger > 70) {
					shoot(5);
				}
				else if (beamCharger > 60) {
					shoot(4);
				}
				else if (beamCharger > 50) {
					shoot(3);
				}
				else if (beamCharger > 40){
					shoot(2);
				}
				else {
					shoot(1);
				}
			}
			beamCharger = 0;
			resetBeamCharge = true;
		}

		// Movement
		glm::vec2 mov = glm::vec2(0.f, 0.f);
		float speed = 5;
		Camera* cam = Camera::getInstance();
		std::map<string, bool> arrow;
		arrow["UP"] = Game::instance().getSpecialKey(GLUT_KEY_UP);
		arrow["DOWN"] = Game::instance().getSpecialKey(GLUT_KEY_DOWN);
		arrow["RIGHT"] = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
		arrow["LEFT"] = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
		if (arrow["UP"] && !arrow["DOWN"]) {							// MOVE UP
			mov.y -= 1.f;
			if (sprite->animation() != MOVE_UP)
				sprite->changeAnimation(MOVE_UP);
			if (cam->collisionUp(posEntity, entitySize, 0.f))
				mov.y += 1.f;
		}
		if (arrow["DOWN"] && !arrow["UP"]) {							// MOVE DOWN
			mov.y += 1.f;
			if (cam->collisionDown(posEntity, entitySize, 0.f))
				mov.y -= 1.f;
			if (sprite->animation() != MOVE_DOWN)
				sprite->changeAnimation(MOVE_DOWN);
		}
		if (arrow["RIGHT"] && !arrow["LEFT"]) {							// MOVE RIGHT
			mov.x += 1.f;
			if (cam->collisionRight(posEntity, entitySize, 0.f))
				mov.x -= 1.f;
		}
		if (arrow["LEFT"] && !arrow["RIGHT"]) {							// MOVE LEFT
			mov.x -= 1.f;
			if (cam->collisionLeft(posEntity, entitySize, 0.f))
				mov.x += 1.f;
		}
		if (!arrow["UP"] && !arrow["DOWN"]) {
			if (sprite->animation() != GO_BACK && sprite->animation() != STAND)
				sprite->changeAnimation(GO_BACK);
		}

		if (mov.x != 0.f && mov.y != 0.f) {
			mov = glm::normalize(mov);
		}
		mov.x = float(mov.x * speed);
		mov.y = float(mov.y * speed);

		if (map->collision(posEntity, glm::ivec2(int(mov.x), int(mov.y)), entitySize))
			if (collisionsActive) startExplosion();
		
		posEntity.x = float(float(posEntity.x) + mov.x);
		posEntity.y = float(float(posEntity.y) + mov.y);

		if (collisionsActive) {
			// Add collision with other entities
			vector<pair<string, string>> collisions = scene->getCollisions(this);
			for (pair<string, string> e : collisions) {
				if (e.first == "RedPlane" || e.first == "EnemyBullet") {
					startExplosion();
					break;
				}
			}
		}		

		// Adapt to camera movement
		posEntity += cam->getSpeed();
		if (cam->collisionRight(posEntity, entitySize, 0.f))
			posEntity -= cam->getSpeed();
		if (map->collisionMoveRight(posEntity, entitySize))
			if (collisionsActive) startExplosion();

		sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
	}
	else if (state == EXPLODING || state == DEAD) {
		ShootingEntity::explode();
	}
}

void Player::shoot(int level)
{
	PassiveEntity* newBullet;
	if (level == 0) {
		newBullet = new SpaceshipBullet();
		newBullet->init(*texProgram, map);
	}
	else {
		newBullet = new SpaceshipBeam();
		newBullet->init(*texProgram, map, level);
	}
	glm::ivec2 bulletSize = newBullet->getSize();
	glm::ivec2 pos;
	pos.x = posEntity.x + entitySize.x - 10;
	pos.y = posEntity.y + 18 - bulletSize.y / 2;
	newBullet->setPosition(pos);
	newBullet->setMovementVector(glm::ivec2(20.f, 0.f));
	addBullet(newBullet);
}

void Player::startExplosion() 
{
	mciSendString(TEXT("play sounds/playerDead.wav"), NULL, 0, NULL);
	
 	Entity::startExplosion();
	delete sprite;
	glm::ivec2 prevEntitySize = entitySize;
	entitySize = glm::ivec2(64, 64);
	spritesheet.loadFromFile("images/spaceship_explosion.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.125, 1), &spritesheet, texProgram);
	sprite->setNumberAnimations(2);

		int keyframesPerSec = 40;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

		sprite->setAnimationSpeed(1, keyframesPerSec);
		sprite->setAnimationLooping(1, false);
		for (int i = 0.f; i < 8; i += 1)
			sprite->addKeyframe(1, glm::vec2(0.125f * float(i), 0.f));

	sprite->changeAnimation(1);
	if (prevEntitySize != entitySize) {
		// Adjust entity position for the different in size between ALIVE sprite and EXPLODING sprite.
		glm::ivec2 diffSize = prevEntitySize - entitySize;
		posEntity.x = posEntity.x + float(diffSize.x / 2);
		posEntity.y = posEntity.y + float(diffSize.y / 2);
	}
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}
