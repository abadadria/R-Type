#include "Force.h"
#include "ForceBullet.h"
#include "ForceMissile.h"
#include "ForceRay.h"

void Force::init(ShaderProgram& shaderProgram, TileMap* tileMap, Player* player)
{
	ShootingEntity::init(shaderProgram, tileMap);
	this->attached = false;
	this->unattachedMovementVec = glm::ivec2(5, 0);
	this->player = player;
	this->currentLevel = 1;
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
	Camera* cam = Camera::getInstance();
	glm::ivec2 camPos = cam->getPos();
	glm::ivec2 camSize = cam->getSize();
	posEntity.x = camPos.x - entitySize.x;
	posEntity.y = camPos.y + camSize.y / 2;
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));

	shootingCounter = 0;
}

void Force::update(int deltaTime, SceneLevel* scene)
{
	ShootingEntity::update(deltaTime, scene);
	if (state == ALIVE) {
		levelDownTimer -= 1;
		if (levelDownTimer == 0)
			levelDown();
		if (!attached) {
			// Movement
			posEntity.x += unattachedMovementVec.x;
			Camera* cam = Camera::getInstance();
			if (cam->collisionRight(posEntity, entitySize, -50.f))
				posEntity.x -= unattachedMovementVec.x;
			posEntity.x = int(float(posEntity.x) + cam->getSpeed().x);
			sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
			// Shooting
			shootingCounter += 1;
			while (shootingCounter > 20) {
				shootingCounter -= 20;
				shoot(0);
			}
			// Collisions
			scene->doAllCollisions(this);
		}
		else {
			// Movement
			// Copy player position
			glm::ivec2 posPlayer = player->getPosition();
			glm::ivec2 sizePlayer = player->getSize();
			posEntity.x = posPlayer.x + sizePlayer.x;
			if (currentLevel == 3)
				posEntity.x = posPlayer.x + sizePlayer.x - 10;
			posEntity.y = posPlayer.y + 18 - entitySize.y / 2;
			sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
			// Shooting
			shootingCounter += 1;
			int framesPerShot;
			if (currentLevel == 1) {
				framesPerShot = 20;
				while (shootingCounter > framesPerShot) {
					shootingCounter -= framesPerShot;
					shoot(0);
				}
			}
			else if (currentLevel == 2) {
				framesPerShot = 70;
				while (shootingCounter > framesPerShot) {
					shootingCounter -= framesPerShot;
					shoot(0);
				}
			}
		}
		
	}
}

string Force::getType() const
{
	return "Force";
}

void Force::doCollision(Entity* entity, SceneLevel* scene)
{
	string type = entity->getType();
	if (type == "Player") {
		attached = true;
		player->attach(this);
	}
}

void Force::setLevel1()
{
	glm::ivec2 prevSize = entitySize;
	entitySize = glm::ivec2(40, 32);
	delete sprite;
	spritesheet.loadFromFile("images/force1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.125, 1.f), &spritesheet, getShaderProgram());
	sprite->setNumberAnimations(1);

		int keyframesPerSec = 17;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->setAnimationLooping(0, true);
		for (int i = 0.f; i < 6; ++i)
			sprite->addKeyframe(0, glm::vec2(0.125f * float(i), 0.f));

	sprite->changeAnimation(0);
	
	posEntity.y += (prevSize.y / 2 - entitySize.y / 2);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));

	currentLevel = 1;

	shootingCounter = 0;
}

void Force::setLevel2()
{
	glm::ivec2 prevSize = entitySize;
	delete sprite;
	entitySize = glm::ivec2(54, 44);
	spritesheet.loadFromFile("images/force2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.125, 1.f), &spritesheet, getShaderProgram());
	sprite->setNumberAnimations(1);

		int keyframesPerSec = 17;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->setAnimationLooping(0, true);
		for (int i = 0.f; i < 6; ++i)
			sprite->addKeyframe(0, glm::vec2(0.125f * float(i), 0.f));

	sprite->changeAnimation(0);

	posEntity.y += (prevSize.y / 2 - entitySize.y / 2);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
	currentLevel = 2;
	levelDownTimer = 60 * 25; // 60 fps * 25 s
	shootingCounter = 0;
}

void Force::setLevel3()
{
	glm::ivec2 prevSize = entitySize;
	delete sprite;
	entitySize = glm::ivec2(62, 56);
	spritesheet.loadFromFile("images/force3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(entitySize, glm::vec2(0.25, 1.f), &spritesheet, getShaderProgram());
	sprite->setNumberAnimations(1);

		int keyframesPerSec = 17;

		sprite->setAnimationSpeed(0, keyframesPerSec);
		sprite->setAnimationLooping(0, true);
		for (int i = 0.f; i < 4; ++i)
			sprite->addKeyframe(0, glm::vec2(0.25f * float(i), 0.f));

	sprite->changeAnimation(0);

	posEntity.x -= 12;
	posEntity.y += (prevSize.y / 2 - entitySize.y / 2);
	sprite->setPosition(glm::vec2(float(posEntity.x), float(posEntity.y)));
	currentLevel = 3;
	levelDownTimer = 60 * 15; // 60 fps * 15 s
	shootingCounter = 0;
}

void Force::levelUp()
{
	if (attached) {
		if (currentLevel == 1) {
			setLevel2();
		}
		else if (currentLevel == 2) {
			setLevel3();
		}
	}
}

void Force::levelDown()
{
	if (currentLevel == 2)
		setLevel1();
	else if (currentLevel == 3)
		setLevel2();
}

int Force::getLevel() const
{
	return currentLevel;
}

void Force::shoot(int level)
{
	switch (currentLevel) {
		case 1:
			{PassiveEntity* newBullet = new ForceBullet();
			newBullet->init(*texProgram, map);
			glm::ivec2 bulletSize = newBullet->getSize();
			glm::ivec2 pos;
			pos.x = posEntity.x + entitySize.x - 10;
			pos.y = posEntity.y + entitySize.y / 2;
			newBullet->setPosition(pos);
			newBullet->setMovementVector(glm::ivec2(20.f, 0.f));
			addBullet(newBullet); }
			break;
		case 2:
			{PassiveEntity* newBullet1 = new ForceMissile();
			PassiveEntity* newBullet2 = new ForceMissile();
			newBullet1->init(*texProgram, map);
			newBullet2->init(*texProgram, map);
			glm::ivec2 bulletSize = newBullet1->getSize();
			glm::ivec2 pos;
			pos.x = posEntity.x + entitySize.x - 10;
			pos.y = posEntity.y + entitySize.y / 2;
			int distance = 60;
			newBullet1->setPosition(glm::ivec2(pos.x, pos.y + distance / 2));
			newBullet2->setPosition(glm::ivec2(pos.x, pos.y - distance / 2));
			newBullet1->setMovementVector(glm::ivec2(12.f, 0.f));
			newBullet2->setMovementVector(glm::ivec2(12.f, 0.f));
			addBullet(newBullet1);
			addBullet(newBullet2); }
			break;
		case 3:
			int framesPerShot = 6;
			while (shootingCounter > framesPerShot) {
				shootingCounter = 0;
				{PassiveEntity* newBullet = new ForceRay();
				newBullet->init(*texProgram, map);
				glm::ivec2 bulletSize = newBullet->getSize();
				glm::ivec2 pos;
				pos.x = posEntity.x + entitySize.x - 10;
				pos.y = posEntity.y + entitySize.y / 2 - bulletSize.y / 2;
				newBullet->setPosition(pos);
				newBullet->setMovementVector(glm::ivec2(20.f, 0.f));
				addBullet(newBullet); }
			}
			break;
	}
	
}

void Force::startExplosion()
{
	Entity::startExplosion();
	delete sprite;
	state = COMPLETELY_DEAD;
}
