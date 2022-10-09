#ifndef _PASSIVEENTITY_INCLUDE
#define _PASSIVEENTITY_INCLUDE


#include "Entity.h"


class PassiveEntity : Entity
{

public:;

	  void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override; // Abstract method
	  void update(int deltaTime) override;
	  void render() override;

};


#endif // _PASSIVEENTITY_INCLUDE