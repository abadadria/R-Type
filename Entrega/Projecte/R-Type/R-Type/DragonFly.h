#ifndef _GRAGON_FLY_INCLUDE
#define _GRAGON_FLY_INCLUDE


#include "AutonomousEntity.h"
#include "SceneLevel.h"


class DragonFly : public AutonomousEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;
	void doCollision(Entity* entity, SceneLevel* scene);

private:
	int shootingCounter;
};

#endif _GRAGON_FLY_INCLUDE

