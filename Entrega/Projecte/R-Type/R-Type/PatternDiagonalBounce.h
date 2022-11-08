#ifndef _PATTERN_DIAGONAL_BOUNCE_INCLUDE
#define _PATTERN_DIAGONAL_BOUNCE_INCLUDE


#include "Pattern.h"
#include "TileMap.h"


class PatternDiagonalBounce : public Pattern
{

public:
	PatternDiagonalBounce(glm::ivec2 initialPos, glm::vec2 initialMovDir, glm::ivec2 entitySize, TileMap* tileMap);

	glm::ivec2 calcNewPosition(int deltaTime) override;

private:
	// Parameters
	glm::ivec2 pos;
	glm::ivec2 entitySize;
	glm::vec2 movDir;
	TileMap* map;
};

#endif _PATTERN_DIAGONAL_BOUNCE_INCLUDE
