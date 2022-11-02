#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

#define ALIVE 0
#define EXPLODING 1
#define DEAD 2
#define COMPLETELY_DEAD 3

class Entity
{

public:
	virtual void init(TileMap* tileMap);
	virtual void update(int deltaTime);
	virtual void render();

	void setPosition(const glm::vec2& pos);

	int getState();

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