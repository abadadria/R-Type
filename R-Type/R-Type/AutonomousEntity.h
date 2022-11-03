#ifndef _AUTONOMOUS_ENTITY_INCLUDE
#define _AUTONOMOUS_ENTITY_INCLUDE


#include "ShootingEntity.h"
#include "Pattern.h"


class AutonomousEntity : public ShootingEntity
{

public:
	virtual void init(ShaderProgram& shaderProgram, TileMap* tileMap, Pattern* movementPattern);
	virtual void update(int deltaTime) override;

private:
	void startExplosion() override;

protected:
	Pattern* movementPattern;

private:
	std::list<PassiveEntity*> passiveEntities;
};

#endif _AUTONOMOUS_ENTITY_INCLUDE