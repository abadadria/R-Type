#include "FinalBossBullet2.h"

void FinalBossBullet2::init(ShaderProgram& shaderProgram, TileMap* tileMap)
{
	PassiveEntity::init(shaderProgram, tileMap);
	entitySize = glm::ivec2(46, 40);
	spritesheet.loadFromFile("images/bossFinal_bullets2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.25f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	int keyframesPerSec = 20;

	sprite->setAnimationSpeed(0, keyframesPerSec);
	sprite->setAnimationLooping(0, true);
	for (int i = 0; i < 4; ++i)
		sprite->addKeyframe(0, glm::vec2(0.25f * float(i), 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}

void FinalBossBullet2::update(int deltaTime, SceneLevel* scene)
{
	PassiveEntity::update(deltaTime);
	if (state == ALIVE) {
		// Collision with other entities
		scene->doAllCollisions(this);
	}
}

string FinalBossBullet2::getType() const
{
	return "FinalBossBullet2";
}

int FinalBossBullet2::getDamage() const
{
	return 10;
}

void FinalBossBullet2::doCollision(Entity* entity, SceneLevel* scene)
{
	string type = entity->getType();
	if (type == "Player" || type == "Force") {
		startExplosion();
	}
}
