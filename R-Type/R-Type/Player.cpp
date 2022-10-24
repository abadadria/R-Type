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


void Player::init(ShaderProgram &shaderProgram)
{
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
	ShootingEntity::setShader(shaderProgram);
}

void Player::update(int deltaTime, glm::vec2 cameraPos, glm::vec2 cameraSize)
{
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	if (Game::instance().getKey(' '))  beamCharger += 1;
	else {
		if (beamCharger != 0) {
			string spriteFile;
			glm::ivec2 sizeSprite;
			glm::vec2 posInSprite;
			glm::vec2 texCoordOffset;
			glm::ivec2 posShoot(posEntity.x, posEntity.y);
			if (beamCharger < 20) { // basic shoot
				posShoot.x = posEntity.x + entitySize.x;
				posShoot.y = posEntity.y + entitySize.y / 3;
 				spriteFile = shootingSpriteFile;
				sizeSprite = sizeSpriteShooting;
				posInSprite = posShootingInSprite;
				texCoordOffset = glm::vec2(0.0, 0.0);
			}
			else {
				spriteFile = beamSpriteFile;
				sizeSprite = sizeSpriteBeam;
				posInSprite = posBeamInSprite;
				if (beamCharger > 60) {
					posShoot.x = posEntity.x + entitySize.x - 8;
					texCoordOffset = glm::vec2(0.5, 0.5);
				}
				else if (beamCharger > 50) {
					posShoot.x = posEntity.x + entitySize.x - 8;
					texCoordOffset = glm::vec2(0.0, 0.5);
				}
				else if (beamCharger > 35) {
					posShoot.x = posEntity.x + entitySize.x - 12;
					texCoordOffset = glm::vec2(0.5, 0.0);
				}
				else texCoordOffset = glm::vec2(0.0, 0.0);
			}
			ShootingEntity::addPassiveEntity(movVecShooting, posShoot, spriteFile, sizeSprite, posInSprite, texCoordOffset);
			beamCharger = 0;
		}
	}

	ShootingEntity::update(deltaTime, cameraPos, cameraSize);

	std::map<string, bool> arrow;
	arrow["UP"] = Game::instance().getSpecialKey(GLUT_KEY_UP);
	arrow["DOWN"] = Game::instance().getSpecialKey(GLUT_KEY_DOWN);
	arrow["RIGHT"] = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
	arrow["LEFT"] = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
	if (arrow["UP"] && !arrow["DOWN"]) {
		posEntity.y -= 3;
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);
		//if (map->collisionMoveUp(posEntity, entitySize, posEntity.y))
		//	posEntity.y += 2;
	}
	if (arrow["DOWN"] && !arrow["UP"]) {
		posEntity.y += 3;
		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		//if (map->collisionMoveDown(posEntity, entitySize, posEntity.y))
		//	posEntity.y -= 2;
	}
	if (arrow["RIGHT"] && !arrow["LEFT"]) {
		posEntity.x += 3;
		//if (map->collisionMoveRight(posEntity, entitySize))
		//	posEntity.x -= 2;
	}
	if (arrow["LEFT"] && !arrow["RIGHT"]) {
		posEntity.x -= 3;
		//if (map->collisionMoveLeft(posEntity, entitySize))
		//	posEntity.x += 2;
	}
	if (!arrow["UP"] && !arrow["DOWN"]) {
		if (sprite->animation() != GO_BACK && sprite->animation() != STAND)
			sprite->changeAnimation(GO_BACK);
	}
	// Adapt to camera movement
	posEntity.x += 1;
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}
