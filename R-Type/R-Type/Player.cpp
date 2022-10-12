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


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/spaceship.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = SpriteSpaceship::createSpriteSpaceship(glm::ivec2(32, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
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
	entitySize = glm::ivec2(32, 16);
	posTileMap = tileMapPos;
	sprite->setPosition(glm::vec2(float(posTileMap.x + posEntity.x), float(posTileMap.y + posEntity.y)));
	ShootingEntity::setShader(shaderProgram);
}

void Player::update(int deltaTime)
{
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	if (Game::instance().getKey(' '))  beamCharger += 1;
	else {
		if (beamCharger != 0) {
			string spriteFile;
			glm::ivec2 sizeSprite;
			glm::vec2 posInSprite;
			glm::vec2 offset;
			glm::ivec2 posShoot(posEntity.x, posEntity.y);
			if (beamCharger < 20) { // basic shoot
				posShoot.x = posEntity.x + entitySize.x;
				posShoot.y = posEntity.y + entitySize.y / 3;
				spriteFile = shootingSpriteFile;
				sizeSprite = sizeSpriteShooting;
				posInSprite = posShootingInSprite;
				offset = glm::vec2(0.0, 0.0);
			}
			else {
				spriteFile = beamSpriteFile;
				sizeSprite = sizeSpriteBeam;
				posInSprite = posBeamInSprite;
				if (beamCharger > 50) {
					posShoot.x = posEntity.x + entitySize.x - 8;
					offset = glm::vec2(0.0, 0.5);
				}
				else if (beamCharger > 35) {
					posShoot.x = posEntity.x + entitySize.x - 12;
					offset = glm::vec2(0.5, 0.0);
				}
				else offset = glm::vec2(0.0, 0.0);
			}
			ShootingEntity::addPassiveEntity(movVecShooting, posShoot, spriteFile, sizeSprite, posInSprite, offset);
			beamCharger = 0;
		}
	}
	ShootingEntity::update(deltaTime);
	std::map<string, bool> arrow;
	arrow["UP"] = Game::instance().getSpecialKey(GLUT_KEY_UP);
	arrow["DOWN"] = Game::instance().getSpecialKey(GLUT_KEY_DOWN);
	arrow["RIGHT"] = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
	arrow["LEFT"] = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
	if (arrow["UP"] && !arrow["DOWN"]) {
		posEntity.y -= 2;
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);
		if (map->collisionMoveUp(posEntity, entitySize, posEntity.y))
			posEntity.y += 2;
	}
	if (arrow["DOWN"] && !arrow["UP"]) {
		posEntity.y += 2;
		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		if (map->collisionMoveDown(posEntity, entitySize, posEntity.y))
			posEntity.y -= 2;
	}
	if (arrow["RIGHT"] && !arrow["LEFT"]) {
		posEntity.x += 2;
		if (map->collisionMoveRight(posEntity, entitySize))
			posEntity.x -= 2;
	}
	if (arrow["LEFT"] && !arrow["RIGHT"]) {
		posEntity.x -= 2;
		if (map->collisionMoveLeft(posEntity, entitySize))
			posEntity.x += 2;
	}
	if (!arrow["UP"] && !arrow["DOWN"] && !arrow["RIGHT"] && !arrow["LEFT"]) {
		if (sprite->animation() != GO_BACK && sprite->animation() != STAND)
			sprite->changeAnimation(GO_BACK);
	}

	sprite->setPosition(glm::vec2(float(posTileMap.x + posEntity.x), float(posTileMap.y + posEntity.y)));
}

void Player::render()
{
	ShootingEntity::render();
}

