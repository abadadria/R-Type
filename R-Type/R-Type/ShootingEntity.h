#ifndef _SHOOTINGENTITY_INCLUDE
#define _SHOOTINGENTITY_INCLUDE


#include <list>
#include "Entity.h"
#include "PassiveEntity.h"


class ShootingEntity : public Entity
{

public:
	virtual void init(ShaderProgram& shaderProgram, TileMap* tileMap);
	virtual void update(int deltaTime);
	void render() override;

	virtual string getType() const override;

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




