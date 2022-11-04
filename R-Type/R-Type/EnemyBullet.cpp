#include "EnemyBullet.h"

void EnemyBullet::init(ShaderProgram& shaderProgram, TileMap* tileMap)
{
	PassiveEntity::init(shaderProgram, tileMap);
	entitySize = glm::ivec2(12, 12);
	spritesheet.loadFromFile("images/enemy_bullet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.25f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

		int keyframesPerSec = 25;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->setAnimationLooping(0, true);
		for (int i = 0; i < 4; ++i)
			sprite->addKeyframe(0, glm::vec2(0.25f * float(i), 0.f));
			
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}

void EnemyBullet::update(int deltaTime)
{
	PassiveEntity::update(deltaTime);
	//TODO collision with entities logic
}
