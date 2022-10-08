#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Entity.h"


class Player : public Entity
{
	
public:;

	  virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override; // Abstract method
	  virtual void update(int deltaTime) override;
	  virtual void render() override;

};


#endif // _PLAYER_INCLUDE


