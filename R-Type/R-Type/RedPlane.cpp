#include "RedPlane.h"
#include "PatternSin.h"
#include <random>

void RedPlane::init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop)
{
	AutonomousEntity::init(shaderProgram, tileMap, 10, drop);
	AutonomousEntity::setPattern(new PatternSin(initialPos, extra, 4, -2, 100));
	entitySize = glm::ivec2(64, 64);
	spritesheet.loadFromFile("images/redplane.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.125, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	int keyframesPerSec = 17;

	sprite->setAnimationSpeed(0, keyframesPerSec);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, keyframesPerSec);
	sprite->setAnimationLooping(1, true);
	for (int i = 0.f; i < 8; i += 1)
		sprite->addKeyframe(1, glm::vec2(0.125f * float(i), 0.f));

	sprite->changeAnimation(1);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));

	shootingCounter = 0;
}

void RedPlane::update(int deltaTime, SceneLevel* scene)
{
	AutonomousEntity::update(deltaTime, scene);
	if (state == ALIVE) {
		// Shooting
		//shootingCounter += 1;
		//while (shootingCounter > 140) {
		//	shootingCounter -= 140;
		//	shoot(0);
		//}

		//Collision with other Entities
		scene->doAllCollisions(this);
	}
}

string RedPlane::getType() const
{
	return "RedPlane";
}

void RedPlane::doCollision(Entity* entity, SceneLevel* scene)
{
	string type = entity->getType();
	if (type == "Player" || type == "SpaceshipBullet" || type == "SpaceshipBeam" ||
		type == "Force" || type == "ForceBullet" || type == "ForceMissile" || type == "ForceRay") {
		reduceLifePoints(entity->getDamage());
		if (getLifePoints() <= 0) {
			scene->increaseScore(200);
			startExplosion();
		}
	}
}
