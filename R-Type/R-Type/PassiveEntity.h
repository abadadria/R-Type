#ifndef _PASSIVEENTITY_INCLUDE
#define _PASSIVEENTITY_INCLUDE


#include "Entity.h"

class SceneLevel;

class PassiveEntity : public Entity
{

public:

	  virtual void init(ShaderProgram& shaderProgram, TileMap* tileMap);
	  virtual void init(ShaderProgram& shaderProgram, TileMap* tileMap, int level);
	  void update(int deltaTime) override;
	  virtual void update(int deltaTime, SceneLevel* scene) = 0;
	  void render() override;

	  void setMovementVector(glm::vec2 movVec);

	  virtual string getType() const override;

protected:
	void startExplosion() override;

private:
	ShaderProgram* texProgram;
	glm::ivec2 movementVector;
};


#endif // _PASSIVEENTITY_INCLUDE