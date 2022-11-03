#ifndef _PATTERN_SIN_INCLUDE
#define _PATTERN_SIN_INCLUDE


#include "Pattern.h"


class PatternSin : public Pattern
{

public:
	PatternSin(int initialAngle, int angleStep, int xSpeed, int amplitude);

	glm::ivec2 calcNewPosition(int deltaTime, glm::ivec2 currentPos);

private:
	// Parameters
	int initialAngle, angleStep,
		xSpeed, amplitude;

	// State
	int currentAngle;
};

#endif _PATTERN_SIN_INCLUDE