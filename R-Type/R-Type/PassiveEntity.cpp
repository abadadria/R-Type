#include "PassiveEntity.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>


void PassiveEntity::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	
}

void PassiveEntity::update(int deltaTime)
{
	Entity::update(deltaTime);
}

void PassiveEntity::render()
{
	Entity::render();
}
