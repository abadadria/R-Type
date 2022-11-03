#ifndef _PATTERN_SIN_INCLUDE
#define _PATTERN_SIN_INCLUDE


#include "Pattern.h"


class PatternSin : public Pattern
{

public:
	PatternSin(glm::ivec2 initialPos, int initialAngle, int angleStep, int xSpeed, int amplitude);

	glm::ivec2 calcNewPosition(int deltaTime) override;

private:
	// Parameters
	glm::ivec2 pos;
	int angleStep, xSpeed, amplitude;

	// State
	int currentAngle;
};

#endif _PATTERN_SIN_INCLUDE