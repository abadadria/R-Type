#include "ShootingEntity.h"
#include <iostream>


ShootingEntity::~ShootingEntity()
{
	for (std::list<PassiveEntity*>::iterator it = passiveEntities.begin(); it != passiveEntities.end();) {
		(*it)->kill();
		delete (*it);
		passiveEntities.erase(it++);
	}
}

void ShootingEntity::init(ShaderProgram& shaderProgram, TileMap* tileMap) {
	Entity::init(tileMap);
	this->texProgram = &shaderProgram;
}

void ShootingEntity::update(int deltaTime, SceneLevel* scene)
{
	Entity::update(deltaTime);
	for (std::list<PassiveEntity*>::iterator it = passiveEntities.begin(); it != passiveEntities.end();) {
		int state = (*it)->getState();
		if (state == COMPLETELY_DEAD) {
        	delete (*it);
			passiveEntities.erase(it++);
		}
		else {
			(*it)->update(deltaTime, scene);
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

void ShootingEntity::doBulletCollisions(Entity* entity, SceneLevel* scene)
{
	for (PassiveEntity* bullet : passiveEntities)
		bullet->collision(entity, scene);
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
	else if (state == DEAD && passiveEntities.size() == 0)
		state = COMPLETELY_DEAD;
}

ShaderProgram* ShootingEntity::getShaderProgram() const
{
	return texProgram;
}
