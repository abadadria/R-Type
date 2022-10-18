#include "ShootingEntity.h"
#include <iostream>


void ShootingEntity::update(int deltaTime, glm::vec2 cameraPos, glm::vec2 cameraSize)
{
	Entity::update(deltaTime);
	for (std::list<PassiveEntity*>::iterator it = passiveEntities.begin(); it != passiveEntities.end();) {
		(*it)->update(deltaTime);
		float margin = -100.f;
		glm::ivec2 posShoot = (*it)->getPosition();
		std::cout << cameraPos.x << ", " << cameraPos.y;
		if (posShoot.x > (cameraPos.x + cameraSize.x + margin) || posShoot.x < (cameraPos.x - margin) ||
			posShoot.y > (cameraPos.y + cameraSize.y + margin) || posShoot.y < (cameraPos.y - margin)) {
        		delete (*it);
			passiveEntities.erase(it++);
		}
		else {
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