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

void Entity::kill()
{
	delete sprite;
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

int Entity::getDamage() const
{
	return 10;
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

void Entity::collision(Entity* entity, SceneLevel* scene)
{
	Camera* cam = Camera::getInstance();

	// To collision, both entities must be ALIVE and visible in the camera frame
	if ((this->state == ALIVE) && (entity->state == ALIVE) &&
		(cam->inFrame(this->posEntity, this->entitySize)) &&
		(cam->inFrame(entity->posEntity, entity->entitySize))) {

		glm::ivec2 pos = entity->posEntity;
		glm::ivec2 size = entity->entitySize;

		int minx1 = posEntity.x;
		int maxx1 = posEntity.x + entitySize.x;
		int minx2 = pos.x;
		int maxx2 = pos.x + size.x;

		int miny1 = posEntity.y;
		int maxy1 = posEntity.y + entitySize.y;
		int miny2 = pos.y;
		int maxy2 = pos.y + size.y;

		if ((minx1 < maxx2) && (minx2 < maxx1) && (miny1 < maxy2) && (miny2 < maxy1)) {
			entity->doCollision(this, scene);
			this->doCollision(entity, scene);
		}
	}
}

void Entity::startExplosion() {
	state = EXPLODING;
}

void Entity::startDying() {
	state = DEAD;
}

Entity::~Entity() {
	//spritesheet.free();
}
