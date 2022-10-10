#include "ShootingEntity.h"


void ShootingEntity::update(int deltaTime)
{
	Entity::update(deltaTime);
	for (std::list<PassiveEntity*>::iterator it = passiveEntities.begin(); it != passiveEntities.end(); ++it) {
		(*it)->update(deltaTime);
	}
}

void ShootingEntity::render()
{
	Entity::render();
	for (std::list<PassiveEntity*>::iterator it = passiveEntities.begin(); it != passiveEntities.end(); ++it) {
		(*it)->render();
	}
}

void ShootingEntity::addPassiveEntity(glm::ivec2 movVec, glm::ivec2 pos, string spriteFolder, glm::ivec2 sizeSprite, glm::vec2 posInSprite) {
	PassiveEntity* newPassiveEntity = new PassiveEntity{};
	newPassiveEntity->init(posTileMap, texProgram);
	newPassiveEntity->setSprite(spriteFolder, sizeSprite, posInSprite, texProgram);
	newPassiveEntity->setInitialPosition(pos);
	newPassiveEntity->setMovementVector(movVec);
	passiveEntities.push_back(newPassiveEntity);
}

void ShootingEntity::setShader(ShaderProgram texProgram) {
	this->texProgram = texProgram;
}