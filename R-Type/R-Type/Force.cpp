#include "Force.h"
#include "ForceBullet.h"

void Force::init(ShaderProgram& shaderProgram, TileMap* tileMap, Player* player)
{
	ShootingEntity::init(shaderProgram, tileMap);
	this->attached = true;
	this->player = player;
	entitySize = glm::ivec2(40, 32);
	spritesheet.loadFromFile("images/force1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.125, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

		int keyframesPerSec = 17;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->setAnimationLooping(0, true);
		for (int i = 0.f; i < 6;++i)
			sprite->addKeyframe(0, glm::vec2(0.125f * float(i), 0.f));

	sprite->changeAnimation(0);
	copyPosPlayer();

	shootingCounter = 0;
}

void Force::update(int deltaTime, SceneLevel* scene)
{
	ShootingEntity::update(deltaTime, scene);
	if (state == ALIVE) {
		// Movement
		copyPosPlayer();
		// Shooting
		shootingCounter += 1;
		while (shootingCounter > 80) {
			shootingCounter -= 80;
			shoot(0);
		}
		// Collisions
	}
}

string Force::getType() const
{
	return "Force";
}

void Force::shoot(int level)
{
	PassiveEntity* newBullet = new ForceBullet();
	newBullet->init(*texProgram, map);
	glm::ivec2 bulletSize = newBullet->getSize();
	glm::ivec2 pos;
	pos.x = posEntity.x + entitySize.x - 10;
	pos.y = posEntity.y + entitySize.y / 2;
	newBullet->setPosition(pos);
	newBullet->setMovementVector(glm::ivec2(20.f, 0.f));
	addBullet(newBullet);
}

void Force::startExplosion()
{
	Entity::startExplosion();
	delete sprite;
	state = COMPLETELY_DEAD;
}

void Force::copyPosPlayer()
{
	glm::ivec2 posPlayer = player->getPosition();
	glm::ivec2 sizePlayer = player->getSize();
	posEntity.x = posPlayer.x + sizePlayer.x;
	posEntity.y = posPlayer.y;
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}
