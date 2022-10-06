#ifndef _SCENELEVEL_INCLUDE
#define _SCENELEVEL_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class SceneLevel
{

public:
	SceneLevel();
	~SceneLevel();

	void init();
	void update(int deltaTime, bool playing);
	void render();

private:
	void initShaders();

private:
	TileMap* map;
	Player* player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENELEVEL_INCLUDE
