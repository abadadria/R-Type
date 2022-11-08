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
	void init(ShaderProgram& shaderProgram, TileMap* tileMap, int life, bool drop);
	virtual void update(int deltaTime, SceneLevel* scene) override;

	virtual string getType() const override;
	bool getDropPowerUp();

protected:
	void setPattern(Pattern* pattern);
	void shoot(int level) override;
	void startExplosion() override;
	
	void reduceLifePoints(int points);
	int getLifePoints() const;

protected:
	Pattern* movementPattern;

private:
	bool dropPowerUp;
	int lifePoints;
};

#endif _AUTONOMOUS_ENTITY_INCLUDE