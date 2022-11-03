#pragma once
#include "AutonomousEntity.h"
class RedPlane : public AutonomousEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos) override;
	void update(int deltaTime) override;
};

