#include "PassiveEntity.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Sprite.h"
#include "Camera.h"


#define BEAM 1


void PassiveEntity::init(ShaderProgram& shaderProgram, TileMap* tileMap)
{
	Entity::init(tileMap);
	texProgram = &shaderProgram;
}

void PassiveEntity::update(int deltaTime)
{
	// TODO control the module of the movement vector
	Entity::update(deltaTime);
	if (state == ALIVE) {
		Camera* cam = Camera::getInstance();
		if (map->collision(posEntity, movementVector, entitySize) ||
			cam->collision(posEntity+movementVector, entitySize, 50.f))
			startExplosion();
		posEntity += movementVector;
		sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
	}
	
}

void PassiveEntity::render()
{
	Entity::render();
}

void PassiveEntity::setInitialPosition(glm::ivec2 pos) {
	this->posEntity = pos;
}

void PassiveEntity::setMovementVector(glm::ivec2 movVec) {
	this->movementVector = movVec;
}

void PassiveEntity::setSprite(string spriteFolder, glm::ivec2 sizeSprite, glm::vec2 posInSprite, int animationType) {
	spritesheet.loadFromFile(spriteFolder, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(sizeSprite, posInSprite, &spritesheet, texProgram);
	entitySize = sizeSprite;
	// especifico del beam, si alguna passive entity mas lo necesita mirar de cambiar
	if (animationType == BEAM) {
		sprite->setNumberAnimations(1);
		int keyframesPerSec = 40;
		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->setAnimationLooping(0, true);
		bool onlyOnce = true;
		for (int i = 1; i <= 2; ++i) {
			sprite->addKeyframe(0, glm::vec2(posInSprite.x*i, posInSprite.y));
			if (onlyOnce) {
				for (int j = 0; j < 4; ++j) {
					sprite->addKeyframe(0, glm::vec2(posInSprite.x * i, posInSprite.y));
				}
				onlyOnce = false;
			}
		}
		sprite->changeAnimation(0);
	}
	
}

void PassiveEntity::startExplosion() {
	Entity::startExplosion();
	delete sprite;
	state = COMPLETELY_DEAD;
}