#ifndef _PASSIVEENTITY_INCLUDE
#define _PASSIVEENTITY_INCLUDE


#include "Entity.h"


class PassiveEntity : Entity
{

public:

	  void init(ShaderProgram& shaderProgram) override; // Abstract method implementation
	  void update(int deltaTime) override;
	  void render() override;
	  void setMovementVector(glm::ivec2 movVec);
	  void setInitialPosition(glm::ivec2 pos);
	  void setSprite(string spriteFolder, glm::ivec2 sizeSprite, glm::vec2 posInSprite, ShaderProgram* texProgram, glm::vec2 offset);
	  glm::ivec2 getPosition();


private:
	glm::ivec2 movementVector;
};


#endif // _PASSIVEENTITY_INCLUDE