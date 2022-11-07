#include "ForceCoin.h"

void ForceCoin::init(ShaderProgram& shaderProgram, TileMap* tileMap)
{
	PassiveEntity::init(shaderProgram, tileMap);
	entitySize = glm::ivec2(32, 32);
	spritesheet.loadFromFile("images/force_coin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.125f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	int keyframesPerSec = 10;

	sprite->setAnimationSpeed(0, keyframesPerSec);
	sprite->setAnimationLooping(0, true);
	for (int i = 0; i < 6; ++i)
		sprite->addKeyframe(0, glm::vec2(0.125f * float(i), 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}

void ForceCoin::update(int deltaTime, SceneLevel* scene)
{
	PassiveEntity::update(deltaTime);
	if (state == ALIVE) {
		// Collision with other entities
		scene->doAllCollisions(this);
	}
}

string ForceCoin::getType() const
{
	return "ForceCoin";
}

void ForceCoin::doCollision(Entity* entity, SceneLevel* scene)
{
	string type = entity->getType();
	if (type == "Player") {
		startExplosion();
	}
}
