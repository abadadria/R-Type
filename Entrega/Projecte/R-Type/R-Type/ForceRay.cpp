#include "ForceRay.h"

void ForceRay::init(ShaderProgram& shaderProgram, TileMap* tileMap)
{
	PassiveEntity::init(shaderProgram, tileMap);
	entitySize = glm::ivec2(128, 64);
	spritesheet.loadFromFile("images/force3_ray.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.25f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

		int keyframesPerSec = 20;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->setAnimationLooping(0, false);
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 4; ++j)
				sprite->addKeyframe(0, glm::vec2(0.25f * float(j), 0.5f * float(i)));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}

void ForceRay::update(int deltaTime, SceneLevel* scene)
{
	PassiveEntity::update(deltaTime);
	if (state == ALIVE) {
		// Collision with other entities
		scene->doAllCollisions(this);
	}
}

string ForceRay::getType() const
{
	return "ForceRay";
}

int ForceRay::getDamage() const
{
	return 3;
}

void ForceRay::doCollision(Entity* entity, SceneLevel* scene)
{
}
