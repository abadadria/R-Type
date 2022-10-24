#ifndef _SHOOTINGENTITY_INCLUDE
#define _SHOOTINGENTITY_INCLUDE


#include <list>
#include "Entity.h"
#include "PassiveEntity.h"
#include "Camera.h"


class ShootingEntity : public Entity
{

public:

	  virtual void update(int deltaTime);
	  void render() override;
	  void addPassiveEntity(glm::ivec2 movVec, glm::ivec2 pos, string spriteFolder, glm::ivec2 sizeSprite, glm::vec2 posInSprite, glm::vec2 offset);
	  void setShader(ShaderProgram texProgram);

private:
	std::list<PassiveEntity*> passiveEntities;
	ShaderProgram texProgram;
};


#endif // _SHOOTINGENTITY_INCLUDE




