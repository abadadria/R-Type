#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <map>

#include "Player.h"
#include "Game.h"
#include "SpriteSpaceship.h"
#include "PassiveEntity.h"


enum PlayerAnims
{
	STAND, MOVE_UP, MOVE_DOWN, GO_BACK
};


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

int Player::getBeamCharge()
{
	return beamCharger;
}

void Player::update(int deltaTime)
{
	ShootingEntity::update(deltaTime);
	if (state == ALIVE) {
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
		if (Game::instance().getKey(' ')) {
			beamCharger += 1;
			spriteBeamCharge->update(deltaTime);
			spriteBeamCharge->setPosition(glm::ivec2(posEntity.x + 65, posEntity.y + 5));
		}
		else if (beamCharger != 0) {
			glm::ivec2 posShoot(posEntity.x, posEntity.y);
			if (beamCharger < 20) { // basic shoot
				ShootingEntity::shoot(movVecShooting);
			}
			else {
				if (beamCharger > 70) {
					ShootingEntity::shootBeam(movVecShooting, 5);
				}
				else if (beamCharger > 60) {
					ShootingEntity::shootBeam(movVecShooting, 4);
				}
				else if (beamCharger > 50) {
					ShootingEntity::shootBeam(movVecShooting, 3);
				}
				else if (beamCharger > 40){
					ShootingEntity::shootBeam(movVecShooting, 2);
				}
				else {
					ShootingEntity::shootBeam(movVecShooting, 1);
				}
			}
			beamCharger = 0;
			resetBeamCharge = true;
		}

		glm::vec2 dir = glm::vec2(0.f, 0.f);
		int speed = 3;
		Camera* cam = Camera::getInstance();
		std::map<string, bool> arrow;
		arrow["UP"] = Game::instance().getSpecialKey(GLUT_KEY_UP);
		arrow["DOWN"] = Game::instance().getSpecialKey(GLUT_KEY_DOWN);
		arrow["RIGHT"] = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
		arrow["LEFT"] = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
		if (arrow["UP"] && !arrow["DOWN"]) {							// MOVE UP
			posEntity.y -= speed;
			if (sprite->animation() != MOVE_UP)
				sprite->changeAnimation(MOVE_UP);
			if (cam->collisionUp(posEntity, entitySize, 0.f))
				posEntity.y += speed;
			if (map->collisionMoveUp(posEntity, entitySize))
				startExplosion();
		}
		if (arrow["DOWN"] && !arrow["UP"]) {							// MOVE DOWN
			posEntity.y += speed;
			if (cam->collisionDown(posEntity, entitySize, 0.f))
				posEntity.y -= speed;
			if (sprite->animation() != MOVE_DOWN)
				sprite->changeAnimation(MOVE_DOWN);
			if (map->collisionMoveDown(posEntity, entitySize))
				startExplosion();
		}
		if (arrow["RIGHT"] && !arrow["LEFT"]) {							// MOVE RIGHT
			posEntity.x += speed;
			if (cam->collisionRight(posEntity, entitySize, 0.f))
				posEntity.x -= speed;
			if (map->collisionMoveRight(posEntity, entitySize))
				startExplosion();
		}
		if (arrow["LEFT"] && !arrow["RIGHT"]) {							// MOVE LEFT
			posEntity.x -= speed;
			if (cam->collisionLeft(posEntity, entitySize, 0.f))
				posEntity.x += speed;
			if (map->collisionMoveLeft(posEntity, entitySize))
				startExplosion();
		}
		if (!arrow["UP"] && !arrow["DOWN"]) {
			if (sprite->animation() != GO_BACK && sprite->animation() != STAND)
				sprite->changeAnimation(GO_BACK);
		}
		// Adapt to camera movement
		posEntity += cam->getSpeed();
		if (cam->collisionRight(posEntity, entitySize, 0.f))
			posEntity -= cam->getSpeed();
		if (map->collisionMoveRight(posEntity, entitySize))
			startExplosion();

		sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
	}
	else if (state == EXPLODING) {
		ShootingEntity::explode();
	}
}

void Player::startExplosion() {
	Entity::startExplosion();
	// TODO Set animation to explosion
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
