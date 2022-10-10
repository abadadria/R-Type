#include "PassiveEntity.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Sprite.h"


void PassiveEntity::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/shootingShip.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 8), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	posTileMap = tileMapPos;
}

void PassiveEntity::update(int deltaTime)
{
	Entity::update(deltaTime);
	posEntity.x += movementVector.x;
	posEntity.y += movementVector.y;
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

//void PassivaEntity::setSprite()