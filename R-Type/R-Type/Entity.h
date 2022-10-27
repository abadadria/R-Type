#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

# define ALIVE 0
# define EXPLODING 1

class Entity
{

public:
	virtual void init(ShaderProgram& shaderProgram) = 0; // Abstract method
	virtual void update(int deltaTime);
	virtual void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	~Entity();

protected:
	virtual void startExplosion();

protected:
	Sprite* sprite;
	Texture spritesheet;
	glm::ivec2 posEntity;
	glm::ivec2 entitySize;
	TileMap* map;
	int state = ALIVE;
};


#endif