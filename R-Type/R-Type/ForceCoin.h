#ifndef _FORCE_COIN_INCLUDE
#define _FORCE_COIN_INCLUDE


#include "PassiveEntity.h"
#include "SceneLevel.h"


class ForceCoin : public PassiveEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;
	void doCollision(Entity* entity) override;
};

#endif _FORCE_COIN_INCLUDE