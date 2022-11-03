#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "ShootingEntity.h"


class Player : public ShootingEntity
{
	
public:;

	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime) override;

private:
	void startExplosion() override;

private:
	const glm::ivec2 movVecShooting = glm::ivec2(7, 0);
	int beamCharger = 0;
};


#endif // _PLAYER_INCLUDE


