#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	virtual void init();
	virtual void update(int deltaTime);
	virtual void render();

protected:
	void initShaders();

protected:
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	glm::vec2 cameraSize;
	glm::vec2 cameraPos;
};


#endif // _SCENE_INCLUDE

