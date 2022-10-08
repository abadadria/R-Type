#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Entity
{

public:
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

protected:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0; // Abstract method
	virtual void update(int deltaTime);
	virtual void render();

protected:
	Sprite* sprite;
	Texture spritesheet;
	glm::ivec2 posTileMap, posEntity;
	glm::ivec2 entitySize;
	TileMap* map;

};


#endif