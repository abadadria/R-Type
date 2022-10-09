#ifndef _PASSIVEENTITY_INCLUDE
#define _PASSIVEENTITY_INCLUDE


#include "Entity.h"


class PassiveEntity : Entity
{

public:;

	  virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override; // Abstract method
	  virtual void update(int deltaTime) override;
	  virtual void render() override;

};


#endif // _PASSIVEENTITY_INCLUDE