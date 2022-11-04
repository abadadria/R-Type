#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "ShootingEntity.h"


class Player : public ShootingEntity
{
	
public:;

	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime) override;
	void render() override;
	int getBeamCharge();

private:
	void startExplosion() override;

private:
	const glm::ivec2 movVecShooting = glm::ivec2(10, 0);
	int beamCharger;
	bool resetBeamCharge;
	Sprite* spriteBeamCharge;
	Texture spritesheetBeamCharge;
};


#endif // _PLAYER_INCLUDE


