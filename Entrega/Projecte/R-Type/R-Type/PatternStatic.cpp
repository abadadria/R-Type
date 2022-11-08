#include "PatternStatic.h"

PatternStatic::PatternStatic(glm::ivec2 initialPos, glm::ivec2 entitySize) {
    this->pos = initialPos;
    this->entitySize = entitySize;
}

glm::ivec2 PatternStatic::calcNewPosition(int deltaTime)
{
    return pos;
}
