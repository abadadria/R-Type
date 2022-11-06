#ifndef _PATTERN_STATIC_INCLUDE
#define _PATTERN_STATIC_INCLUDE


#include "Pattern.h"
#include "TileMap.h"


class PatternStatic : public Pattern
{

public:
	PatternStatic(glm::ivec2 initialPos, glm::ivec2 entitySize);

	glm::ivec2 calcNewPosition(int deltaTime) override;

private:
	// Parameters
	glm::ivec2 pos;
	glm::ivec2 entitySize;
};

#endif _PATTERN_STATIC_INCLUDE
