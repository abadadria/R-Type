#include "ShootingEntity.h"


void ShootingEntity::update(int deltaTime)
{
	Entity::update(deltaTime);
	for (PassiveEntity passiveEntity : passiveEntities) {
		passiveEntity.update(deltaTime);
	}
}

void ShootingEntity::render()
{
	Entity::render();
	for (PassiveEntity passiveEntity : passiveEntities) {
		passiveEntity.render();
	}
}

void ShootingEntity::addPassiveEntity(glm::ivec2 movVec, glm::ivec2 pos) {
	PassiveEntity newPassiveEntity;
	newPassiveEntity.init(posTileMap, texProgram);
	newPassiveEntity.setInitialPosition(pos);
	newPassiveEntity.setMovementVector(movVec);
	passiveEntities.push_back(newPassiveEntity);
}

void ShootingEntity::setShader(ShaderProgram texProgram) {
	this->texProgram = texProgram;
}