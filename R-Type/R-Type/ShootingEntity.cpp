#include "ShootingEntity.h"


void ShootingEntity::update(int deltaTime)
{
	//implementar colisiones en un futuro
	Entity::update(deltaTime);
	for (std::list<PassiveEntity*>::iterator it = passiveEntities.begin(); it != passiveEntities.end();) {
		(*it)->update(deltaTime);
		glm::ivec2 posShoot = (*it)->getPosition();
		// no hardcodear el tamaño de la pantalla
		if (posShoot.x > 640 || posShoot.x < 0 ||
			posShoot.y > 480 || posShoot.y < 0) {
			delete* it;
			passiveEntities.erase(it++);
		}
		else {
			++it;
		}
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