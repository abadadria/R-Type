#ifndef _AUTONOMOUS_ENTITY_INCLUDE
#define _AUTONOMOUS_ENTITY_INCLUDE


#include "ShootingEntity.h"
#include "Pattern.h"

class SceneLevel; // To fix compilation due to circular includes

class AutonomousEntity : public ShootingEntity
{

public:
	~AutonomousEntity();

	virtual void init(ShaderProgram& shaderProgram, TileMap* tileMap, glm::ivec2 initialPos, int extra, bool drop) = 0;
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, bool drop);
	virtual void update(int deltaTime, SceneLevel* scene);

	virtual string getType() const override;

protected:
	void setPattern(Pattern* pattern);
	void shoot(int level) override;
	void startExplosion() override;

protected:
	Pattern* movementPattern;
	bool dropPowerUp;
};

#endif _AUTONOMOUS_ENTITY_INCLUDE