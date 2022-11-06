#ifndef _PATTERN_DUEL_INCLUDE
#define _PATTERN_DUEL_INCLUDE


#include "Pattern.h"
#include "Player.h"


class PatternDuel : public Pattern
{

public:
	PatternDuel(glm::ivec2 initialPos, glm::vec2 initialMovDir, glm::ivec2 entitySize, int speed);

	glm::ivec2 calcNewPosition(int deltaTime) override;

private:
	// Parameters
	glm::ivec2 pos;
	glm::ivec2 entitySize;
	glm::vec2 movDir;
	Player* player;
	int movementCounter;
	int speed;
};

#endif _PATTERN_DUEL_INCLUDE
