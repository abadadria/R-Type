#include "DragonFlyBullet.h"

void DragonFlyBullet::init(ShaderProgram& shaderProgram, TileMap* tileMap)
{
	PassiveEntity::init(shaderProgram, tileMap);
	entitySize = glm::ivec2(128, 32);
	spritesheet.loadFromFile("images/dragonFly_bullet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.5f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	int keyframesPerSec = 40;

	sprite->setAnimationSpeed(0, keyframesPerSec);
	sprite->setAnimationLooping(0, true);
	for (int i = 0; i < 5; ++i)
		sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}

void DragonFlyBullet::update(int deltaTime, SceneLevel* scene)
{
	PassiveEntity::update(deltaTime);
	if (state == ALIVE) {
		// Collision with other entities
		scene->doAllCollisions(this);
	}
}

string DragonFlyBullet::getType() const
{
	return "DragonFlyBullet";
}

int DragonFlyBullet::getDamage() const
{
	return 10;
}

void DragonFlyBullet::doCollision(Entity* entity, SceneLevel* scene)
{
	string type = entity->getType();
	if (type == "Player" || type == "Force") {
		startExplosion();
	}
}
