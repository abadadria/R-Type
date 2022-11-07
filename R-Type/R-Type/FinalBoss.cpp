#include "FinalBoss.h"
#include "PatternStatic.h"

void FinalBoss::init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop)
{
	initialLife = 3000;
	AutonomousEntity::init(shaderProgram, tileMap, initialLife, drop);
	//entitySize = glm::ivec2(155, 246); // original size
	//entitySize = glm::ivec2(168, 455); // funciona
	entitySize = glm::ivec2(75, 455);
	spriteSize = glm::ivec2(175, 455);
	AutonomousEntity::setPattern(new PatternStatic(initialPos, spriteSize));
	spritesheet.loadFromFile("images/bossFinal.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(spriteSize, glm::vec2(0.25f, 0.125f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);

		int keyframesPerSec = 10;
		for (int i = 0; i < 6; ++i) {
			sprite->setAnimationSpeed(i, keyframesPerSec);
			sprite->setAnimationLooping(i, true);
			for (int j = 0; j < 3; ++j)
				sprite->addKeyframe(i, glm::vec2(0.25f * float(j), 0.125f * float(i)));
		}

		keyframesPerSec = 15;
		sprite->setAnimationSpeed(6, keyframesPerSec);
		sprite->setAnimationLooping(6, true);
		for (int j = 0; j < 3; ++j)
			sprite->addKeyframe(6, glm::vec2(0.25f * float(j), 0.125f * float(6)));

		keyframesPerSec = 20;
		sprite->setAnimationSpeed(7, keyframesPerSec);
		sprite->setAnimationLooping(7, true);
		for (int j = 0; j < 3; ++j)
			sprite->addKeyframe(7, glm::vec2(0.25f * float(j), 0.125f * float(7)));

	actualAnimation = 0;
	sprite->changeAnimation(actualAnimation);

	glm::ivec2 posSprite;
	posSprite.x = posEntity.x - 100;
	posSprite.y = posEntity.y;
	sprite->setPosition(glm::vec2(float(posSprite.x), float(posSprite.y)));

	shootingCounter1 = 0;
	shootingCounter2 = 0;
}

void FinalBoss::update(int deltaTime, SceneLevel* scene)
{
	// Not using AutonomousEntity::update() because of the offset between the sprite and the hitbox
	ShootingEntity::update(deltaTime, scene);
	if (state == ALIVE) {
		// Movement
		posEntity = movementPattern->calcNewPosition(deltaTime);
		Camera* cam = Camera::getInstance();
		if (cam->collision(posEntity, entitySize, 200.f)) {
			startExplosion();
		}

		glm::ivec2 posSprite;
		posSprite.x = posEntity.x - 100;
		posSprite.y = posEntity.y;
		sprite->setPosition(glm::vec2(float(posSprite.x), float(posSprite.y)));
	}
	else if (state == EXPLODING || state == DEAD) {
		ShootingEntity::explode();
	}

	// Normal update()
	if (state == ALIVE) {
		int prevAnimation = actualAnimation;
		int life = getLifePoints();
		if (life > 17500*2) actualAnimation = 0;
		else if (life > float(initialLife) * 0.95f) actualAnimation = 1;
		else if (life > float(initialLife) * 0.8f) actualAnimation = 2;
		else if (life > float(initialLife) * 0.75f) actualAnimation = 3;
		else if (life > float(initialLife) * 0.5f) actualAnimation = 4;
		else if (life > float(initialLife) * 0.3f) actualAnimation = 5;
		else if (life > float(initialLife) * 0.2f) actualAnimation = 6;
		else actualAnimation = 7;

		if (prevAnimation != actualAnimation)
			sprite->changeAnimation(actualAnimation);
		
		// Shooting
		shootingCounter1 += 1;
		while (shootingCounter1 > 20) {
			shootingCounter1 -= 20;
			shoot(2);
		}

		shootingCounter2 += 1;
		while (shootingCounter2 > 30) {
			shootingCounter2 -=30;
			shoot(3);
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
		type == "Force" || type == "ForceBullet" || type == "ForceMissile" || type == "ForceRay") {
		int damage = entity->getDamage();
		reduceLifePoints(damage);
		if (getLifePoints() <= 0) {
			scene->increaseScore(9500);
			startExplosion();
		}
	}
}

void FinalBoss::startExplosion()
{
	Entity::startExplosion();
	delete sprite;
	glm::ivec2 prevEntitySize = entitySize;
	entitySize = glm::ivec2(384, 384);
	spritesheet.loadFromFile("images/enemy_explosion.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.25, 0.5), &spritesheet, texProgram);
	sprite->setNumberAnimations(1);

		int keyframesPerSec = 30;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->setAnimationLooping(0, false);
		sprite->addKeyframe(0, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(0, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(0, glm::vec2(0.75f, 0.f));
		sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(0, glm::vec2(0.25f, 0.f));
		sprite->addKeyframe(0, glm::vec2(0.f, 0.f));


	sprite->changeAnimation(0);
	if (prevEntitySize != entitySize) {
		// Adjust entity position for the different in size between ALIVE sprite and EXPLODING sprite.
		glm::ivec2 diffSize = prevEntitySize - entitySize;
		posEntity.x = posEntity.x + float(diffSize.x / 2);
		posEntity.y = posEntity.y + float(diffSize.y / 2);
	}
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}
