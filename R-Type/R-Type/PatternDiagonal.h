#ifndef _PATTERN_DIAGONAL_INCLUDE
#define _PATTERN_DIAGONAL_INCLUDE


#include "Pattern.h"


class PatternDiagonal : public Pattern
{

public:
	PatternDiagonal(glm::ivec2 initialPos, int initialAngle, int angleStep, int xSpeed, int amplitude);

	glm::ivec2 calcNewPosition(int deltaTime) override;

private:
	// Parameters
	glm::ivec2 pos;
	int angleStep, xSpeed, amplitude;

	// State
	int currentAngle;
};

#endif _PATTERN_DIAGONAL_INCLUDE
