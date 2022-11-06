#include "PatternDiagonal.h"

PatternDiagonal::PatternDiagonal(glm::ivec2 initialPos, glm::vec2 initialMovDir, glm::ivec2 entitySize, TileMap* tileMap) {
    this->pos = initialPos;
    this->movDir = initialMovDir;
    this->map = tileMap;
    this->entitySize = entitySize;
}

glm::ivec2 PatternDiagonal::calcNewPosition(int deltaTime)
{
    glm::ivec2 provPosX = pos;
    provPosX.x = pos.x + movDir.x;
    
    glm::ivec2 provPosY = pos;
    provPosY.y = pos.y + movDir.y;

    if (map->collisionMoveDown(provPosY, entitySize) || map->collisionMoveUp(provPosY, entitySize)) {
        movDir.y *= -1;
    }

    if ((map->collisionMoveLeft(provPosX, entitySize) || map->collisionMoveRight(provPosX, entitySize))) {
        movDir.x *= -1;
    }

    glm::ivec2 newPos;
    newPos.x = pos.x + movDir.x;
    newPos.y = pos.y + movDir.y;

    pos = newPos;
    return newPos;
}
