#include "PatternDuel.h"

PatternDuel::PatternDuel(glm::ivec2 initialPos, glm::vec2 initialMovDir, glm::ivec2 entitySize) {
    this->pos = initialPos;
    this->movDir = initialMovDir;
    this->entitySize = entitySize;
}

glm::ivec2 PatternDuel::calcNewPosition(int deltaTime)
{
    player = Player::getInstance();
    glm::vec2 posPlayer = player->getPosition();

    // hacer que se mueva hacia el player pero manteniendo una cierta distancia x

    glm::ivec2 newPos;
    newPos.x = pos.x + movDir.x;
    newPos.y = pos.y + movDir.y;

    return pos;
    pos = newPos;
    //return newPos;
}
