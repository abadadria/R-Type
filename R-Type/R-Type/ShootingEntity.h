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
	void addPassiveEntity(glm::ivec2 movVec, glm::ivec2 pos, string spriteFolder, glm::ivec2 sizeSprite, glm::vec2 posInSprite, int animationType);
	void shoot(glm::ivec2 movVec);

protected:
	virtual void explode();

protected:
	ShaderProgram* texProgram;

private:
	std::list<PassiveEntity*> passiveEntities;
	
};


#endif // _SHOOTINGENTITY_INCLUDE




