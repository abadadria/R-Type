#include "SilverRobot.h"
#include "PatternDiagonalBounce.h"

void SilverRobot::init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop)
{
	AutonomousEntity::init(shaderProgram, tileMap, drop);
	entitySize = glm::ivec2(64, 64);
	AutonomousEntity::setPattern(new PatternDiagonalBounce(initialPos, glm::vec2(-2, -2),  entitySize, tileMap));
	spritesheet.loadFromFile("images/silverRobot.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.125f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);
	
	int keyframesPerSec = 2;

	sprite->setAnimationSpeed(0, keyframesPerSec);
	sprite->setAnimationSpeed(1, keyframesPerSec);
	sprite->setAnimationLooping(0, true);
	sprite->setAnimationLooping(1, true);

	sprite->addKeyframe(0, glm::vec2(0.125f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.125f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.250f, 0.f));

	sprite->addKeyframe(1, glm::vec2(0.625f, 0.f));
	sprite->addKeyframe(1, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(1, glm::vec2(0.625f, 0.f));
	sprite->addKeyframe(1, glm::vec2(0.75f, 0.f));

	sprite->changeAnimation(0);
	
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));

	shootingCounter = 0;
}

void SilverRobot::update(int deltaTime, SceneLevel* scene)
{
	glm::vec2 prevPos = posEntity;
	AutonomousEntity::update(deltaTime, scene);
	if (state == ALIVE) {
		// Check direction
		if (prevPos.x > posEntity.x) // Moving to the left
			sprite->changeAnimation(0);
		else // Moving to the right
			sprite->changeAnimation(1);

		// Shooting
		shootingCounter += 1;
		while (shootingCounter > 180) {
			shootingCounter -= 180;
			shoot(0);
		}

		//Collision with other Entities
		scene->doAllCollisions(this);
	}
}

string SilverRobot::getType() const
{
	return "SilverRobot";
}

void SilverRobot::doCollision(Entity* entity)
{
	string type = entity->getType();
	if (type == "Player" || type == "SpaceshipBullet" || type == "SpaceshipBeam" ||
		type == "Force" || type == "ForceBullet" || type == "ForceMissile") {
		// TODO score
		startExplosion();
	}
}
