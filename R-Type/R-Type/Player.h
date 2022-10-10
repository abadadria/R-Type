#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "ShootingEntity.h"


class Player : public ShootingEntity
{
	
public:;

	  void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override; // Abstract method
	  void update(int deltaTime) override;
	  void render() override;
};


#endif // _PLAYER_INCLUDE


