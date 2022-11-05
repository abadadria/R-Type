#ifndef _ENEMY_BULLET_INCLUDE
#define _ENEMY_BULLET_INCLUDE


#include "PassiveEntity.h"
#include "SceneLevel.h"

class EnemyBullet : public PassiveEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;
};

#endif _ENEMY_BULLET_INCLUDE