#include "AutonomousEntity.h"
#include "PatternSin.h"
#include "Camera.h"


AutonomousEntity::~AutonomousEntity() {
	delete movementPattern;
}

void AutonomousEntity::init(ShaderProgram& shaderProgram, TileMap* tileMap)
{
	ShootingEntity::init(shaderProgram, tileMap);
}

void AutonomousEntity::update(int deltaTime)
{
	ShootingEntity::update(deltaTime);
	if (state == ALIVE) {
		// Movement
		posEntity = movementPattern->calcNewPosition(deltaTime);
		Camera* cam = Camera::getInstance();
		if (cam->collision(posEntity, entitySize, 200.f)) {
			startExplosion();
		}
		sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
	}
	else if (state == EXPLODING) {
		ShootingEntity::explode();
	}
}

void AutonomousEntity::setPattern(Pattern* pattern) {
	this->movementPattern = pattern;
}

void AutonomousEntity::startExplosion()
{
	Entity::startExplosion();
	//TODO do specific stuff
}
