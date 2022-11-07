#include "ForceBullet.h"

void ForceBullet::init(ShaderProgram& shaderProgram, TileMap* tileMap)
{
	PassiveEntity::init(shaderProgram, tileMap);
	entitySize = glm::ivec2(32, 8);
	spritesheet.loadFromFile("images/force1_bullet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	int keyframesPerSec = 1;

	sprite->setAnimationSpeed(0, keyframesPerSec);
	sprite->setAnimationLooping(0, false);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}

void ForceBullet::update(int deltaTime, SceneLevel* scene)
{
	PassiveEntity::update(deltaTime);
	if (state == ALIVE) {
		// Collision with other entities
		scene->doAllCollisions(this);
	}
}

string ForceBullet::getType() const
{
	return "ForceBullet";
}

void ForceBullet::doCollision(Entity* entity, SceneLevel* scene)
{
	string type = entity->getType();
	if (type == "RedPlane" || type == "SilverRobot" || type == "Turret" || type == "DragonFly") {
		startExplosion();
	}
}
