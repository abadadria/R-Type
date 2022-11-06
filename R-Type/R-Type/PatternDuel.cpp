#include "PatternDuel.h"

PatternDuel::PatternDuel(glm::ivec2 initialPos, glm::vec2 initialMovDir, glm::ivec2 entitySize, int speed) {
    this->pos = initialPos;
    this->movDir = initialMovDir;
    this->entitySize = entitySize;
    this->speed = speed;
    movementCounter = 0;
}

glm::ivec2 PatternDuel::calcNewPosition(int deltaTime)
{
    player = Player::getInstance();
    glm::vec2 posPlayer = player->getPosition();

    if (posPlayer.y > pos.y) movDir.y = speed / 2;
    else if (posPlayer.y == pos.y) movDir.y = 0;
    else movDir.y = -speed/2;

    movementCounter += speed;
    while (movementCounter > 60) {
        movementCounter -= 60;
        if (posPlayer.x > pos.x) movDir.x = speed;
        else movDir.x = -speed;

        if (pos.x - posPlayer.x < 300) movDir.x = speed;
    }

    glm::ivec2 newPos;
    newPos.x = pos.x + movDir.x;
    newPos.y = pos.y + movDir.y;

    pos = newPos;
    return newPos;
}
