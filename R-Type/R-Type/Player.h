#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "SpriteSpaceship.h"
#include "TileMap.h"


// Player is basically a SpriteSpaceship that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	
private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	SpriteSpaceship *sprite;
	TileMap *map;
	glm::ivec2 playerSize;
};


#endif // _PLAYER_INCLUDE


