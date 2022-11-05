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
	void update(int deltaTime, SceneLevel* scene);
	void render() override;

	virtual string getType() const override;
	//First is the result and second the getType() of the bullets
	pair<bool, string> getBulletCollisions(Entity* entity) const;

protected:
	void addBullet(PassiveEntity* bullet);
	virtual void shoot(int level) = 0;

	virtual void explode();
	virtual void die();

protected:
	ShaderProgram* texProgram;

private:
	std::list<PassiveEntity*> passiveEntities;
	
};


#endif // _SHOOTINGENTITY_INCLUDE




