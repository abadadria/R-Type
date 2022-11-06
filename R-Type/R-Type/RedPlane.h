#ifndef _RED_PLANE_INCLUDE
#define _RED_PLANE_INCLUDE


#include "AutonomousEntity.h"
#include "SceneLevel.h"


class RedPlane : public AutonomousEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;
	void doCollision(Entity* entity) override;

private:
	int shootingCounter;
};

#endif _RED_PLANE_INCLUDE