#ifndef _FINAL_BOSS_BULLET1_INCLUDE
#define _FINAL_BOSS_BULLET1_INCLUDE


#include "PassiveEntity.h"
#include "SceneLevel.h"

class FinalBossBullet1 : public PassiveEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;
	int getDamage() const override;
	void doCollision(Entity* entity, SceneLevel* scene);
};

#endif _FINAL_BOSS_BULLET1_INCLUDE



