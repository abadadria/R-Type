#include "PassiveEntity.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Sprite.h"


void PassiveEntity::init(ShaderProgram& shaderProgram)
{
}

void PassiveEntity::update(int deltaTime)
{
	//control the module of the movement vector
	Entity::update(deltaTime);
	posEntity += movementVector;
	Entity::setPosition(posEntity);
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

void PassiveEntity::setSprite(string spriteFolder, glm::ivec2 sizeSprite, glm::vec2 posInSprite, ShaderProgram& texProgram, glm::vec2 offset) {
	spritesheet.loadFromFile(spriteFolder, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(sizeSprite, posInSprite, &spritesheet, &texProgram);
	sprite->setDisplayOffset(offset);
}

glm::ivec2 PassiveEntity::getPosition() {
	return posEntity;
}