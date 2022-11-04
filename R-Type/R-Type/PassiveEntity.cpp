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

void PassiveEntity::init(ShaderProgram& shaderProgram, TileMap* tileMap, int level) {}

void PassiveEntity::update(int deltaTime)
{
	// TODO control the module of the movement vector
	Entity::update(deltaTime);
	if (state == ALIVE) {
		Camera* cam = Camera::getInstance();
		if (map->collision(posEntity, movementVector, entitySize) ||
			cam->collision(posEntity + movementVector, entitySize, 50.f))
			startExplosion();
		posEntity += movementVector;
		sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
	}
	
}

void PassiveEntity::render()
{
	Entity::render();
}

void PassiveEntity::setMovementVector(glm::vec2 movVec) {
	this->movementVector = movVec;
}

void PassiveEntity::startExplosion() {
	Entity::startExplosion();
	delete sprite;
	state = COMPLETELY_DEAD;
}