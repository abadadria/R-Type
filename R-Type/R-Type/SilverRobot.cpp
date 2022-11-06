#include "SilverRobot.h"
#include "PatternSin.h"

void SilverRobot::init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop)
{
	AutonomousEntity::init(shaderProgram, tileMap, drop);
	AutonomousEntity::setPattern(new PatternSin(initialPos, extra, 4, -1, 100));
	entitySize = glm::ivec2(68, 68);
	spritesheet.loadFromFile("images/silverRobot.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.17, 0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	int keyframesPerSec = 17;

	sprite->setAnimationSpeed(0, keyframesPerSec);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, keyframesPerSec);
	sprite->setAnimationLooping(1, true);
	for (int i = 0; i < 3; ++i)
		sprite->addKeyframe(1, glm::vec2(0.17f * float(i), 0.f));
	sprite->changeAnimation(1);
	/*
	int keyframesPerSec = 10;

	sprite->setAnimationSpeed(0, keyframesPerSec);
	sprite->setAnimationLooping(0, true);

	for (int i = 0; i < 3; ++i)
		sprite->addKeyframe(1, glm::vec2(0.17f * float(i), 0.f));

	sprite->changeAnimation(0);
	*/
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));

	shootingCounter = 0;
}

void SilverRobot::update(int deltaTime, SceneLevel* scene)
{
	AutonomousEntity::update(deltaTime, scene);
	if (state == ALIVE) {
		// Shooting
		shootingCounter += 1;
		while (shootingCounter > 180) {
			shootingCounter -= 180;
			shoot(0);
		}

		//Collision with other Entities
		vector<pair<string, string>> collisions = scene->getCollisions(this);
		for (pair<string, string> e : collisions) {
			if (e.first == "Player" || e.first == "SpaceshipBullet" || e.first == "SpaceshipBeam") {
				scene->increaseScore(200);
				startExplosion();
				break;
			}
		}
	}
}

string SilverRobot::getType() const
{
	return "SilverRobot";
}
