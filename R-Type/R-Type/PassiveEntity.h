#ifndef _PASSIVEENTITY_INCLUDE
#define _PASSIVEENTITY_INCLUDE


#include "Entity.h"


class PassiveEntity : public Entity
{

public:

	  virtual void init(ShaderProgram& shaderProgram, TileMap* tileMap);
	  virtual void update(int deltaTime) override;
	  void render() override;

	  void setMovementVector(glm::ivec2 movVec);
	  void setInitialPosition(glm::ivec2 pos);
	  void setSprite(string spriteFolder, glm::ivec2 sizeSprite, glm::vec2 posInSprite, int animationType);

private:
	void startExplosion() override;

private:
	ShaderProgram* texProgram;
	glm::ivec2 movementVector;
};


#endif // _PASSIVEENTITY_INCLUDE