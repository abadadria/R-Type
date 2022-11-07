#ifndef _DRAGON_FLY_BULLET_INCLUDE
#define _DRAGON_FLY_BULLET_INCLUDE


#include "PassiveEntity.h"
#include "SceneLevel.h"

class DragonFlyBullet : public PassiveEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;
	void doCollision(Entity* entity, SceneLevel* scene);
};

#endif _DRAGON_FLY_BULLET_INCLUDE

