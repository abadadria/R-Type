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

string Entity::getType() const
{
	return "Entity";
}

glm::ivec2 Entity::getPosition() const
{
	return posEntity;
}

glm::ivec2 Entity::getSize() const
{
	return entitySize;
}

int Entity::getState() const
{
	return state;
}

bool Entity::collision(Entity* entity)
{
	glm::ivec2 pos = entity->getPosition();
	glm::ivec2 size = entity->getSize();

	int minx1 = posEntity.x;
	int maxx1 = posEntity.x + entitySize.x;
	int minx2 = pos.x;
	int maxx2 = pos.x + size.x;

	int miny1 = posEntity.y;
	int maxy1 = posEntity.y + entitySize.y;
	int miny2 = pos.y;
	int maxy2 = pos.y + size.y;

	return (minx1 < maxx2) && (minx2 < maxx1) &&
		   (miny1 < maxy2) && (miny2 < maxy1);
}

void Entity::startExplosion() {
	state = EXPLODING;
}

void Entity::startDying() {
	state = DEAD;
}

Entity::~Entity() {
}
