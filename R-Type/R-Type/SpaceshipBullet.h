#ifndef _SPACESHIP_BULLET_INCLUDE
#define _SPACESHIP_BULLET_INCLUDE


#include "PassiveEntity.h"


class SpaceshipBullet : public PassiveEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime) override;


};

#endif _SPACESHIP_BULLET_INCLUDE