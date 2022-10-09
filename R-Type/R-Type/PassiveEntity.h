#ifndef _PASSIVEENTITY_INCLUDE
#define _PASSIVEENTITY_INCLUDE


#include "Entity.h"


class PassiveEntity : Entity
{

public:;

	  void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override; // Abstract method
	  void update(int deltaTime) override;
	  void render() override;
	  void setMovementVector(glm::ivec2 movVec);
	  void setInitialPosition(glm::ivec2 pos);


private:
	glm::ivec2 movementVector;
};


#endif // _PASSIVEENTITY_INCLUDE