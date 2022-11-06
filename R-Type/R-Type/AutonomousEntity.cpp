#include "AutonomousEntity.h"
#include "Camera.h"
#include "EnemyBullet.h"
#include "Player.h"


AutonomousEntity::~AutonomousEntity() {
	delete movementPattern;
}

void AutonomousEntity::init(ShaderProgram& shaderProgram, TileMap* tileMap)
{
	ShootingEntity::init(shaderProgram, tileMap);
}

void AutonomousEntity::update(int deltaTime, SceneLevel* scene)
{
	ShootingEntity::update(deltaTime, scene);
	if (state == ALIVE) {
		// Movement
		posEntity = movementPattern->calcNewPosition(deltaTime);
		Camera* cam = Camera::getInstance();
		if (cam->collision(posEntity, entitySize, 100.f)) {
			startDying();
		}
		sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
	}
	else if (state == EXPLODING) {
		ShootingEntity::explode();
	}
	else if (state == DEAD) {
		ShootingEntity::die();
	}
}

string AutonomousEntity::getType() const
{
	return "AutonomousEntity";
}

void AutonomousEntity::setPattern(Pattern* pattern) {
	this->movementPattern = pattern;
}

void AutonomousEntity::shoot(int level)
{
	PassiveEntity* newBullet = new EnemyBullet();
	newBullet->init(*texProgram, map);
	glm::ivec2 bulletSize = newBullet->getSize();
	glm::vec2 pos;
	pos.x = float(posEntity.x) + float(entitySize.x) / 2.f - float(bulletSize.x) / 2.f;
	pos.y = float(posEntity.y) + float(entitySize.y) / 2.f - float(bulletSize.y) / 2.f;
	newBullet->setPosition(glm::ivec2(int(pos.x), int(pos.y)));
	Player* p = Player::getInstance();
	glm::ivec2 pPos = p->getPosition();
	glm::ivec2 pSize = p->getSize();
	glm::vec2 pCenter;
	pCenter.x = float(pPos.x) + float(pSize.x) / 2.f;
	pCenter.y = float(pPos.y) + float(pSize.y) / 2.f;
	glm::vec2 dir = pCenter - pos;
	dir = glm::normalize(dir);
	glm::ivec2 movementVector;
	movementVector.x = float(dir.x * 6.f);
	movementVector.y = float(dir.y * 6.f);
	newBullet->setMovementVector(movementVector);
	addBullet(newBullet);
}

void AutonomousEntity::startExplosion()
{
	Entity::startExplosion();
	delete sprite;
	glm::ivec2 prevEntitySize = entitySize;
	entitySize = glm::ivec2(64, 64);
	spritesheet.loadFromFile("images/enemy_explosion.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.25, 0.5), &spritesheet, texProgram);
	sprite->setNumberAnimations(2);

	int keyframesPerSec = 40;

	sprite->setAnimationSpeed(0, keyframesPerSec);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(1, keyframesPerSec);
	sprite->setAnimationLooping(1, false);
	sprite->addKeyframe(1, glm::vec2(0.25f , 0.5f));
	sprite->addKeyframe(1, glm::vec2(0.f , 0.5f));
	sprite->addKeyframe(1, glm::vec2(0.75f , 0.f));
	sprite->addKeyframe(1, glm::vec2(0.5f , 0.f));
	sprite->addKeyframe(1, glm::vec2(0.25f , 0.f));
	sprite->addKeyframe(1, glm::vec2(0.f , 0.f));


	sprite->changeAnimation(1);
	if (prevEntitySize != entitySize) {
		// Adjust entity position for the different in size between ALIVE sprite and EXPLODING sprite.
		glm::ivec2 diffSize = prevEntitySize - entitySize;
		posEntity.x = posEntity.x + float(diffSize.x / 2);
		posEntity.y = posEntity.y + float(diffSize.y / 2);
	}
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
}

void AutonomousEntity::startDying() {
	Entity::startDying();
	delete sprite;
}