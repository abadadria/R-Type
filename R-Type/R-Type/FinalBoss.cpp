#include "FinalBoss.h"
#include "PatternStatic.h"

void FinalBoss::init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop)
{
	AutonomousEntity::init(shaderProgram, tileMap, 40000, drop);
	//entitySize = glm::ivec2(155, 246); // original size
	//entitySize = glm::ivec2(168, 455); // funciona
	entitySize = glm::ivec2(175, 455); //
	AutonomousEntity::setPattern(new PatternStatic(initialPos, entitySize));
	spritesheet.loadFromFile("images/bossFinal.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.25f, 0.125f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);

	int keyframesPerSec = 1;
	for (int i = 0; i < 8; ++i) {
		sprite->setAnimationSpeed(i, keyframesPerSec);
		sprite->setAnimationLooping(i, true);
		for (int j = 0; j < 3; ++j)
			sprite->addKeyframe(i, glm::vec2(0.25f * float(j), 0.125f * float(i)));
	}
	actualAnimation = 0;
	sprite->changeAnimation(actualAnimation);

	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));

	shootingCounter = 0;
}

void FinalBoss::update(int deltaTime, SceneLevel* scene)
{
	AutonomousEntity::update(deltaTime, scene);
	if (state == ALIVE) {
		int prevAnimation = actualAnimation;
		int life = getLifePoints();
		if (life > 17500*2) actualAnimation = 0;
		else if (life > 15000*2) actualAnimation = 1;
		else if (life > 12500*2) actualAnimation = 2;
		else if (life > 10000*2) actualAnimation = 3;
		else if (life > 7500*2) actualAnimation = 4;
		else if (life > 5000*2) actualAnimation = 5;
		else if (life > 2500*2) actualAnimation = 6;
		else actualAnimation = 7;

		if (prevAnimation != actualAnimation)
			sprite->changeAnimation(actualAnimation);
		
		// Shooting
		shootingCounter += 1;
		while (shootingCounter > 50) {
			shootingCounter -= 50;
			shoot(0);
		}

		//Collision with other Entities
		scene->doAllCollisions(this);
	}
}

string FinalBoss::getType() const
{
	return "FinalBoss";
}

void FinalBoss::doCollision(Entity* entity, SceneLevel* scene)
{
	string type = entity->getType();
	if (type == "Player" || type == "SpaceshipBullet" || type == "SpaceshipBeam" ||
		type == "Force" || type == "ForceBullet" || type == "ForceMissile") {
		int damage = entity->getDamage();
		reduceLifePoints(damage);
		if (getLifePoints() <= 0) {
			scene->increaseScore(9500);
			startExplosion();
		}
	}
}
