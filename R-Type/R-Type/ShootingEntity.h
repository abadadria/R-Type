#ifndef _SHOOTINGENTITY_INCLUDE
#define _SHOOTINGENTITY_INCLUDE


#include <list>
#include "Entity.h"
#include "PassiveEntity.h"

class SceneLevel;

class ShootingEntity : public Entity
{

public:
	~ShootingEntity();

	virtual void init(ShaderProgram& shaderProgram, TileMap* tileMap);
	virtual void update(int deltaTime, SceneLevel* scene);
	void render() override;

	virtual string getType() const override;
	void doBulletCollisions(Entity* entity, SceneLevel* scene);

protected:
	void addBullet(PassiveEntity* bullet);
	virtual void shoot(int level) = 0;

	virtual void explode();

	ShaderProgram* getShaderProgram() const;

protected:
	ShaderProgram* texProgram;

private:
	std::list<PassiveEntity*> passiveEntities;
	
};


#endif // _SHOOTINGENTITY_INCLUDE




