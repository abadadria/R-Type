#include "SpaceshipBeam.h"

void SpaceshipBeam::init(ShaderProgram& shaderProgram, TileMap* tileMap, int level)
{
	PassiveEntity::init(shaderProgram, tileMap);
	this->level = level;
	switch (level) {
		case 1:
			entitySize = glm::ivec2(32, 24);
			spritesheet.loadFromFile("images/spaceship_beam1.png", TEXTURE_PIXEL_FORMAT_RGBA);
			break;
		case 2:
			entitySize = glm::ivec2(64,24);
			spritesheet.loadFromFile("images/spaceship_beam2.png", TEXTURE_PIXEL_FORMAT_RGBA);
			break;
		case 3:
			entitySize = glm::ivec2(96, 28);
			spritesheet.loadFromFile("images/spaceship_beam3.png", TEXTURE_PIXEL_FORMAT_RGBA);
			break;
		case 4:
			entitySize = glm::ivec2(128, 28);
			spritesheet.loadFromFile("images/spaceship_beam4.png", TEXTURE_PIXEL_FORMAT_RGBA);
			break;
		case 5:
			entitySize = glm::ivec2(160, 32);
			spritesheet.loadFromFile("images/spaceship_beam5.png", TEXTURE_PIXEL_FORMAT_RGBA);
			break;
	}
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.5f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

		int keyframesPerSec = 25;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->setAnimationLooping(0, true);
		for (int i = 0; i < 5; ++i)
			sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}

void SpaceshipBeam::update(int deltaTime, SceneLevel* scene)
{
	PassiveEntity::update(deltaTime);
	// Collision with other entities
	scene->doAllCollisions(this);

}

string SpaceshipBeam::getType() const
{
	return "SpaceshipBeam";
}

int SpaceshipBeam::getDamage() const
{
	return (level + 1) / 2;
}

void SpaceshipBeam::doCollision(Entity* entity, SceneLevel* scene)
{
}
