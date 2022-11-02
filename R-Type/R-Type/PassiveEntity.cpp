#include "PassiveEntity.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Sprite.h"
#include "Camera.h"


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

void PassiveEntity::setSprite(string spriteFolder, glm::ivec2 sizeSprite, glm::vec2 posInSprite, glm::vec2 offset) {
	spritesheet.loadFromFile(spriteFolder, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(sizeSprite, posInSprite, &spritesheet, texProgram);
	sprite->setDisplayOffset(offset);
}

void PassiveEntity::startExplosion() {
	Entity::startExplosion();
	delete sprite;
	state = COMPLETELY_DEAD;
}