#include "ShootingEntity.h"


void ShootingEntity::update(int deltaTime)
{
	Entity::update(deltaTime);
	for (std::list<PassiveEntity*>::iterator it = passiveEntities.begin(); it != passiveEntities.end();) {
		(*it)->update(deltaTime);
		glm::ivec2 posShoot = (*it)->getPosition();
		// TODO no hardcodear el tamaño de la pantalla
		/*if (posShoot.x > 640 || posShoot.x < 0 ||
			posShoot.y > 480 || posShoot.y < 0) {
			delete *it;
			passiveEntities.erase(it++);
		}
		else {*/
			++it;
		//}
	}
}

void ShootingEntity::render()
{
	for (PassiveEntity* ps : passiveEntities) {
		ps->render();
	}
	Entity::render();
}

void ShootingEntity::addPassiveEntity(glm::ivec2 movVec, glm::ivec2 pos, string spriteFolder, glm::ivec2 sizeSprite, glm::vec2 posInSprite, glm::vec2 offset) {
	PassiveEntity* newPassiveEntity = new PassiveEntity{};
	newPassiveEntity->init(posTileMap, texProgram);
	newPassiveEntity->setSprite(spriteFolder, sizeSprite, posInSprite, texProgram, offset);
	newPassiveEntity->setInitialPosition(pos);
	newPassiveEntity->setMovementVector(movVec);
	passiveEntities.push_back(newPassiveEntity);
}

void ShootingEntity::setShader(ShaderProgram texProgram) {
	this->texProgram = texProgram;
}