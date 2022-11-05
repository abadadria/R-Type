#include "RedPlane.h"
#include "PatternSin.h"

void RedPlane::init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos)
{
	AutonomousEntity::init(shaderProgram, tileMap);
	AutonomousEntity::setPattern(new PatternSin(initialPos, 0, 4, -1, 100));
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
		shootingCounter += 1;
		while (shootingCounter > 80) {
			shootingCounter -= 80;
			shoot(0);
		}

		//Collision with other Entities
		vector<pair<string, string>> collisions = scene->getCollisions(this);
		for (pair<string, string> e : collisions) {
			if (e.first == "Player" || e.first == "SpaceshipBullet" || e.first == "SpaceshipBeam") {
				scene->increaseScore(200);
				startExplosion();
			}
				
		}
	}
}

string RedPlane::getType() const
{
	return "RedPlane";
}
