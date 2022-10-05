#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include <map>


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND, STAND_UP, STAND_DOWN, MOVE_UP, MOVE_DOWN, GO_BACK
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/spaceship.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = SpriteSpaceship::createSpriteSpaceship(glm::ivec2(32, 16), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
		sprite->setAnimationSpeed(STAND, 4);
		sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));

		sprite->setAnimationSpeed(STAND_UP, 4);
		sprite->addKeyframe(STAND_UP, glm::vec2(0.5f, 0.f));

		sprite->setAnimationSpeed(STAND_DOWN, 4);
		sprite->addKeyframe(STAND_DOWN, glm::vec2(0.5f, 0.5f));

		sprite->setAnimationSpeed(MOVE_UP, 4);
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.5f, 0.5f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.25f, 0.0f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.5f, 0.0f));

		sprite->setAnimationSpeed(MOVE_DOWN, 4);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.5f, 0.5f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25f, 0.0f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.5f, 0.0f));

		sprite->setAnimationSpeed(GO_BACK, 4);
		sprite->addKeyframe(GO_BACK, glm::vec2(0.5f, 0.5f));
		sprite->addKeyframe(GO_BACK, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(GO_BACK, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(GO_BACK, glm::vec2(0.25f, 0.0f));
		sprite->addKeyframe(GO_BACK, glm::vec2(0.5f, 0.0f));
	
	sprite->changeAnimation(0);
	playerSize = glm::ivec2(32, 16);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	std::map<string, bool> arrow;
	arrow["UP"] = Game::instance().getSpecialKey(GLUT_KEY_UP);
	arrow["DOWN"] = Game::instance().getSpecialKey(GLUT_KEY_DOWN);
	arrow["RIGHT"] = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
	arrow["LEFT"] = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
	if (arrow["UP"] && !arrow["DOWN"]) {
		posPlayer.y -= 2;
		if (sprite->animation() != MOVE_UP && sprite->animation() != STAND_UP)
			sprite->changeAnimation(MOVE_UP);
		//if (map->collisionMoveRight(posPlayer, playerSize))
		//	posPlayer.y += 2;
	}
	if (arrow["DOWN"] && !arrow["UP"]) {
		posPlayer.y += 2;
		if (sprite->animation() != MOVE_DOWN && sprite->animation() != STAND_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		//if (map->collisionMoveRight(posPlayer, playerSize))
		//	posPlayer.y -= 2;
	}
	if (arrow["RIGHT"] && !arrow["LEFT"]) {
		posPlayer.x += 2;
		//if (map->collisionMoveRight(posPlayer, playerSize))
		//	posPlayer.x -= 2;
	}
	if (arrow["LEFT"] && !arrow["RIGHT"]) {
		posPlayer.x -= 2;
		//if (map->collisionMoveRight(posPlayer, playerSize))
		//	posPlayer.x += 2;
	}
	if (!arrow["UP"] && !arrow["DOWN"] && !arrow["RIGHT"] && !arrow["LEFT"]) {
		if (sprite->animation() != GO_BACK && sprite->animation() != STAND)
			sprite->changeAnimation(GO_BACK);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




