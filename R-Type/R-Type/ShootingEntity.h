#ifndef _SHOOTINGENTITY_INCLUDE
#define _SHOOTINGENTITY_INCLUDE


#include <list>
#include "Entity.h"
#include "PassiveEntity.h"


class ShootingEntity : public Entity
{

public:;

	  void update(int deltaTime) override;
	  void render() override;
	  void addPassiveEntity(glm::ivec2 movVec, glm::ivec2 pos);
	  void setShader(ShaderProgram texProgram);

private:
	std::list<PassiveEntity> passiveEntities;
	ShaderProgram texProgram;
};


#endif // _SHOOTINGENTITY_INCLUDE




