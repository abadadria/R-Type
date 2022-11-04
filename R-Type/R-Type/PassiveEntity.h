#ifndef _PASSIVEENTITY_INCLUDE
#define _PASSIVEENTITY_INCLUDE


#include "Entity.h"


class PassiveEntity : public Entity
{

public:

	  virtual void init(ShaderProgram& shaderProgram, TileMap* tileMap);
	  virtual void init(ShaderProgram& shaderProgram, TileMap* tileMap, int level);
	  virtual void update(int deltaTime) override;
	  void render() override;

	  void setMovementVector(glm::vec2 movVec);

private:
	void startExplosion() override;

private:
	ShaderProgram* texProgram;
	glm::ivec2 movementVector;
};


#endif // _PASSIVEENTITY_INCLUDE