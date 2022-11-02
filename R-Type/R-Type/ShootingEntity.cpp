#include "ShootingEntity.h"
#include <iostream>


void ShootingEntity::update(int deltaTime)
{
	Entity::update(deltaTime);
	for (std::list<PassiveEntity*>::iterator it = passiveEntities.begin(); it != passiveEntities.end();) {
		(*it)->update(deltaTime);
		glm::ivec2 posShoot = (*it)->getPosition();
		Camera* cam = Camera::getInstance();
		if (cam->collision(posShoot, glm::vec2(0.f, 0.f), 50.f)) {
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
	newPassiveEntity->setSprite(spriteFolder, sizeSprite, posInSprite, texProgram, offset);
	newPassiveEntity->setInitialPosition(pos);
	newPassiveEntity->setMovementVector(movVec);
	passiveEntities.push_back(newPassiveEntity);
}

void ShootingEntity::setShader(ShaderProgram* texProgram) {
	this->texProgram = texProgram;
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
		state == COMPLETELY_DEAD;
}