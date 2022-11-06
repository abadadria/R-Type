#ifndef _SILVER_ROBOT_INCLUDE
#define _SILVER_ROBOT_INCLUDE


#include "AutonomousEntity.h"
#include "SceneLevel.h"


class SilverRobot : public AutonomousEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;

private:
	int shootingCounter;
};

#endif _SILVER_ROBOT_INCLUDE