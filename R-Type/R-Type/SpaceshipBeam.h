#ifndef _SPACESHIP_BEAM_INCLUDE
#define _SPACESHIP_BEAM_INCLUDE


#include "PassiveEntity.h"
#include "SceneLevel.h"

class SpaceshipBeam : public PassiveEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, int level) override;
	void update(int deltaTime, SceneLevel* scene) override;

	string getType() const override;
	void doCollision(Entity* entity) override;

private:
	int level;
};

#endif _SPACESHIP_BEAM_INCLUDE