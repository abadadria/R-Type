#include "DragonFly.h"
#include "PatternDuel.h"

void DragonFly::init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop)
{
	AutonomousEntity::init(shaderProgram, tileMap, drop);
	entitySize = glm::ivec2(68, 68);
	AutonomousEntity::setPattern(new PatternDuel(initialPos, glm::vec2(-1, 0), entitySize));
	spritesheet.loadFromFile("images/dragonFly.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.5f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	int keyframesPerSec = 2;

	sprite->setAnimationSpeed(0, keyframesPerSec);
	sprite->setAnimationSpeed(1, keyframesPerSec);
	sprite->setAnimationLooping(0, true);
	sprite->setAnimationLooping(1, true);

	sprite->addKeyframe(0, glm::vec2(0, 0.f));
	sprite->addKeyframe(1, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(0);

	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));

	shootingCounter = 0;
}

void DragonFly::update(int deltaTime, SceneLevel* scene)
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
			shoot(1);
		}

		//Collision with other Entities
		vector<pair<string, string>> collisions = scene->getCollisions(this);
		for (pair<string, string> e : collisions) {
			if (e.first == "Player" || e.first == "SpaceshipBullet" || e.first == "SpaceshipBeam" ||
				e.first == "Force" || e.first == "ForceBullet") {
				scene->increaseScore(200);
				startExplosion();
				break;
			}
		}
	}
}

string DragonFly::getType() const
{
	return "DragonFly";
}
