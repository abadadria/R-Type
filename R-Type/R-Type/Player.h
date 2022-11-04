#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "ShootingEntity.h"


class Player : public ShootingEntity
{
	
public:
	static Player* getInstance();
	~Player();

	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime) override;
	void render() override;
	int getBeamCharge();

private:
	Player();

	void shoot(glm::ivec2 movVec, int level) override;

	void startExplosion() override;

private:
	static Player* instance;

	const glm::ivec2 movVecShooting = glm::ivec2(10, 0);
	int beamCharger;
	bool resetBeamCharge;
	Sprite* spriteBeamCharge;
	Texture spritesheetBeamCharge;
};


#endif // _PLAYER_INCLUDE


