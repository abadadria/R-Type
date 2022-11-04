#ifndef _SPACESHIP_BEAM_INCLUDE
#define _SPACESHIP_BEAM_INCLUDE


#include "PassiveEntity.h"


class SpaceshipBeam : public PassiveEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, int level) override;
	void update(int deltaTime) override;

private:
	int level;
};

#endif _SPACESHIP_BEAM_INCLUDE