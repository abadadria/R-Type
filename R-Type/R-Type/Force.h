#pragma once
#include "ShootingEntity.h"
#include "Player.h"
class Force : public ShootingEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, Player* player);
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;

protected:
	void shoot(int level) override;
	void startExplosion() override;

private:
	bool attached;
	Player* player;
	
	int shootingCounter;
	glm::ivec2 unattachedMovementVec;
};

