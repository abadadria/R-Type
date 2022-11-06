#ifndef _TURRET_INCLUDE
#define _TURRET_INCLUDE


#include "AutonomousEntity.h"
#include "SceneLevel.h"
#include "Player.h"


class Turret : public AutonomousEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;

private:
	int shootingCounter;
	Player* player;
};

#endif _TURRET_INCLUDE