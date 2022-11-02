#include "Entity.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <map>

#include "Game.h"

void Entity::init(TileMap* tileMap) {
	map = tileMap;
}

void Entity::update(int deltaTime)
{
	if (state != DEAD && state != COMPLETELY_DEAD)
		sprite->update(deltaTime);
}

void Entity::render()
{
	if (state != DEAD && state != COMPLETELY_DEAD)
		sprite->render();
}

void Entity::setPosition(const glm::vec2& pos)
{
	posEntity = pos;
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}

int Entity::getState()
{
	return state;
}

void Entity::startExplosion() {
	state = EXPLODING;
}

Entity::~Entity() {
	delete sprite;
}
