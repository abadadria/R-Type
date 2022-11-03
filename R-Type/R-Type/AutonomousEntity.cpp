#include "AutonomousEntity.h"
#include "Camera.h"


void AutonomousEntity::init(ShaderProgram& shaderProgram, TileMap* tileMap, Pattern* movementPattern)
{
	ShootingEntity::init(shaderProgram, tileMap);
	this->movementPattern = movementPattern;
	entitySize = glm::ivec2(64, 64);
	spritesheet.loadFromFile("images/redplane.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.125, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

		int keyframesPerSec = 25;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

		sprite->setAnimationSpeed(1, keyframesPerSec);
		sprite->setAnimationLooping(1, true);
		for (int i = 0.f; i < 8; i += 1)
			sprite->addKeyframe(1, glm::vec2(0.125f * float(i), 0.f));

	sprite->changeAnimation(1);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}

void AutonomousEntity::update(int deltaTime)
{
	ShootingEntity::update(deltaTime);
	if (state == ALIVE) {
		// Shooting

		// Movement
		posEntity = movementPattern->calcNewPosition(deltaTime, posEntity);
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

void AutonomousEntity::startExplosion()
{
	Entity::startExplosion();
}
