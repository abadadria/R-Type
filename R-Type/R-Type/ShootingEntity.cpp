#include "ShootingEntity.h"
#include <iostream>


void ShootingEntity::init(ShaderProgram& shaderProgram, TileMap* tileMap) {
	Entity::init(tileMap);
	this->texProgram = &shaderProgram;
}

void ShootingEntity::update(int deltaTime)
{
	Entity::update(deltaTime);
	for (std::list<PassiveEntity*>::iterator it = passiveEntities.begin(); it != passiveEntities.end();) {
		int state = (*it)->getState();
		if (state == COMPLETELY_DEAD) {
        	delete (*it);
			passiveEntities.erase(it++);
		}
		else {
			(*it)->update(deltaTime);
			++it;
		}
	}
}

void ShootingEntity::render()
{
	for (PassiveEntity* ps : passiveEntities) {
		ps->render();
	}
	Entity::render();
}

string ShootingEntity::getType() const
{
	return "ShootingEntity";
}

void ShootingEntity::addBullet(PassiveEntity* bullet)
{
	passiveEntities.push_back(bullet);
}

void ShootingEntity::explode() {
	// Check if animation is finished
	// Then delete sprite
	if (state == EXPLODING && sprite->isAnimationFinished()) {
		delete sprite;
		state = DEAD;
	}
	// Check if there are missing bullets
	// If not set state to COMPLETELY_DEAD for the parent scope to delete the object
	if (state == DEAD && passiveEntities.size() == 0)
		state = COMPLETELY_DEAD;
}

void ShootingEntity::die() {
	if (state == DEAD && passiveEntities.size() == 0)
		state = COMPLETELY_DEAD;
}