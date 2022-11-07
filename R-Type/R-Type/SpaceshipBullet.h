#ifndef _SPACESHIP_BULLET_INCLUDE
#define _SPACESHIP_BULLET_INCLUDE


#include "PassiveEntity.h"
#include "SceneLevel.h"

class SpaceshipBullet : public PassiveEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;
	void doCollision(Entity* entity, SceneLevel* scene);

};

#endif _SPACESHIP_BULLET_INCLUDE