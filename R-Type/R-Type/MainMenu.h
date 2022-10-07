#pragma once

#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"


class MainMenu
{

public:
	MainMenu();
	~MainMenu();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:

	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE



