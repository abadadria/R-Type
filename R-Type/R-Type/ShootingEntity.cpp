#include "ShootingEntity.h"
#include "SpaceshipBullet.h"
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

void ShootingEntity::addPassiveEntity(glm::ivec2 movVec, glm::ivec2 pos, string spriteFolder, glm::ivec2 sizeSprite, glm::vec2 posInSprite, int animationType) {
	PassiveEntity* newPassiveEntity = new PassiveEntity{};
	newPassiveEntity->init(*texProgram, map);
	newPassiveEntity->setSprite(spriteFolder, sizeSprite, posInSprite, animationType);
	newPassiveEntity->setInitialPosition(pos);
	newPassiveEntity->setMovementVector(movVec);
	passiveEntities.push_back(newPassiveEntity);
}

void ShootingEntity::shoot(glm::ivec2 movVec)
{
	PassiveEntity* newBullet = new SpaceshipBullet();;
	newBullet->init(*texProgram, map);
	glm::ivec2 pos;
	pos.x = posEntity.x + entitySize.x;
	pos.y = posEntity.y + entitySize.y / 2;
	newBullet->setPosition(pos);
	newBullet->setMovementVector(movVec);
	passiveEntities.push_back(newBullet);
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