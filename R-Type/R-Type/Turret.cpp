#include "Turret.h"
#include "PatternStatic.h"

void Turret::init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop)
{
	AutonomousEntity::init(shaderProgram, tileMap, 10, drop);
	entitySize = glm::ivec2(32, 32);
	AutonomousEntity::setPattern(new PatternStatic(initialPos, entitySize));
	spritesheet.loadFromFile("images/turret.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.125f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	int keyframesPerSec = 1;
	for (int i = 0; i < 6; ++i) {
		sprite->setAnimationSpeed(i, keyframesPerSec);
		sprite->setAnimationLooping(i, false);
	}

	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(1, glm::vec2(0.125f, 0.f));
	sprite->addKeyframe(2, glm::vec2(0.250f, 0.f));

	sprite->addKeyframe(3, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(4, glm::vec2(0.125f, 0.5f));
	sprite->addKeyframe(5, glm::vec2(0.250f, 0.5f));

	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));

	shootingCounter = 0;
}

void Turret::update(int deltaTime, SceneLevel* scene)
{
	AutonomousEntity::update(deltaTime, scene);
	if (state == ALIVE) {
		// check direction and change animation
		player = Player::getInstance();
		glm::vec2 posPlayer = player->getPosition();
		if (posPlayer.x > posEntity.x) {
			if (posEntity.y < 512/ 2) sprite->changeAnimation(5);
			else sprite->changeAnimation(2);
		}
		else {
			if (posEntity.x - posPlayer.x > 640 /2) {
				if (posEntity.y < 512 / 2) sprite->changeAnimation(3);
				else sprite->changeAnimation(0);
			}
			else if (posEntity.x - posPlayer.x > 640 / 4) {
				if (posEntity.y < 512 / 2) sprite->changeAnimation(4);
				else sprite->changeAnimation(1);
			}
			else {
				if (posEntity.y < 512 / 2) sprite->changeAnimation(5);
				else sprite->changeAnimation(2);
			}
		}

		// Shooting
		shootingCounter += 1;
		while (shootingCounter > 50) {
			shootingCounter -= 50;
			if (posPlayer.x < posEntity.x) shoot(0);
		}

		//Collision with other Entities
		scene->doAllCollisions(this);
	}
}

string Turret::getType() const
{
	return "Turret";
}

void Turret::doCollision(Entity* entity, SceneLevel* scene)
{
	string type = entity->getType();
	if (type == "Player" || type == "SpaceshipBullet" || type == "SpaceshipBeam" ||
		type == "Force" || type == "ForceBullet" || type == "ForceMissile" || type == "ForceRay") {
		reduceLifePoints(entity->getDamage());
		if (getLifePoints() <= 0) {
			scene->increaseScore(400);
			startExplosion();
		}
	}
}
