#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

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
	Sprite* sprite;
	Texture spritesheet;
	glm::ivec2 posEntity;
	glm::ivec2 entitySize;
	TileMap* map;

};


#endif