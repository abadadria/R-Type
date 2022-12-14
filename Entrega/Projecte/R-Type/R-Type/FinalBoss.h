#ifndef _FINAL_BOSS_INCLUDE
#define _FINAL_BOSS_INCLUDE


#include "AutonomousEntity.h"
#include "SceneLevel.h"


class FinalBoss : public AutonomousEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;
	void doCollision(Entity* entity, SceneLevel* scene);

private:
	int shootingCounter1;
	int shootingCounter2;
	int actualAnimation;
};

#endif _FINAL_BOSS_INCLUDE