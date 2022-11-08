#ifndef _PATTERN_INCLUDE
#define _PATTERN_INCLUDE

#include <glm/glm.hpp>


class Pattern
{
public:
	virtual glm::ivec2 calcNewPosition(int deltaTime) = 0;

};

#endif _PATTERN_INCLUDE