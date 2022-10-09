#include "PassiveEntity.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Sprite.h"


void PassiveEntity::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setPosition(glm::vec2(float(posTileMap.x + posEntity.x), float(posTileMap.y + posEntity.y)));
	posTileMap = tileMapPos;
}

void PassiveEntity::update(int deltaTime)
{
	Entity::update(deltaTime);
	posEntity.x += movementVector.x;
	posEntity.y += movementVector.y;
	sprite->setPosition(glm::vec2(float(posTileMap.x + posEntity.x), float(posTileMap.y + posEntity.y)));
}

void PassiveEntity::render()
{
	Entity::render();
}

void PassiveEntity::setInitialPosition(glm::ivec2 pos) {
	posEntity = pos;
}

void PassiveEntity::setMovementVector(glm::ivec2 movVec) {
	movementVector = movVec;
}