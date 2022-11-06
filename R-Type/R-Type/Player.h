#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "ShootingEntity.h"

class SceneLevel; // To fix compilation due to circular includes

class Player : public ShootingEntity
{
	
public:
	static Player* getInstance();
	//~Player();

	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime, SceneLevel* scene) override;
	void render() override;

	int getBeamCharge();
	void changeCollisionsActive();
	bool getCollisionsActive();

	string getType() const override;
	void doCollision(Entity* entity) override;

private:
	Player();

	void shoot(int level) override;

	void startExplosion() override;

private:
	static Player* instance;

	bool collisionsActive;

	const glm::ivec2 movVecShooting = glm::ivec2(10, 0);
	int beamCharger;
	bool resetBeamCharge;
	Sprite* spriteBeamCharge;
	Texture spritesheetBeamCharge;
};


#endif // _PLAYER_INCLUDE


