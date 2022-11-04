#ifndef _RED_PLANE_INCLUDE
#define _RED_PLANE_INCLUDE


#include "AutonomousEntity.h"


class RedPlane : public AutonomousEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos) override;
	void update(int deltaTime) override;

private:
	int shootingCounter;
};

#endif _RED_PLANE_INCLUDE