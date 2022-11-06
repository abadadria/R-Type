#include "ForceMissile.h"
#include "SceneLEvel.h"

void ForceMissile::init(ShaderProgram& shaderProgram, TileMap* tileMap)
{
	PassiveEntity::init(shaderProgram, tileMap);
	
	// Init missile
	entitySize = glm::ivec2(32, 8);
	spritesheet.loadFromFile("images/force2_missile.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

		int keyframesPerSec = 1;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->setAnimationLooping(0, false);
		sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));

	// Init flames
	flamesSize = glm::ivec2(28, 24);
	spritesheetFlames.loadFromFile("images/force2_missile_fire.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteFlames = Sprite::createSprite(flamesSize, glm::vec2(0.125f, 1.f), &spritesheetFlames, &shaderProgram);
	spriteFlames->setNumberAnimations(1);

		keyframesPerSec = 40;

		spriteFlames->setAnimationSpeed(0, keyframesPerSec);
		spriteFlames->setAnimationLooping(0, true);
		for (int i = 0; i < 7; ++i)
			spriteFlames->addKeyframe(0, glm::vec2(0.125f * float(i), 0.f));

	spriteFlames->changeAnimation(0);
	glm::vec2 posFlames;
	posFlames.x = float(posEntity.x - flamesSize.x);
	posFlames.y = float(posEntity.y + entitySize.y / 2 - flamesSize.y / 2);
	spriteFlames->setPosition(glm::vec2(float(posFlames.x), float(posFlames.y)));
}

void ForceMissile::update(int deltaTime, SceneLevel* scene)
{
	PassiveEntity::update(deltaTime);
	if (state == ALIVE) {
		// Collision with other entities
		vector<pair<string, string>> collisions = scene->getCollisions(this);
		for (pair<string, string> e : collisions) {
			if (e.first == "RedPlane") {
				startExplosion();
				break;
			}
		}
		spriteFlames->update(deltaTime);
		glm::vec2 posFlames;
		posFlames.x = float(posEntity.x - flamesSize.x);
		posFlames.y = float(posEntity.y + entitySize.y / 2 - flamesSize.y / 2);
		spriteFlames->setPosition(glm::vec2(float(posFlames.x), float(posFlames.y)));
	}
}

void ForceMissile::render()
{
	if (state == ALIVE)
		spriteFlames->render();
	PassiveEntity::render();
}

void ForceMissile::kill()
{
	delete spriteFlames;
	Entity::kill();
}

string ForceMissile::getType() const
{
	return "ForceMissile";
}