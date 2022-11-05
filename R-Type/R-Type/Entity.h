#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <string>

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

	virtual string getType() const;
	glm::ivec2 getPosition() const;
	glm::ivec2 getSize() const;
	int getState() const;

	bool collision(Entity* entity);

	~Entity();

protected:
	virtual void startExplosion();
	virtual void startDying();

protected:
	Sprite* sprite;
	Texture spritesheet;
	glm::ivec2 posEntity;
	glm::ivec2 entitySize;
	TileMap* map;
	int state = ALIVE;
};


#endif