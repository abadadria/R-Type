#include "PatternDuel.h"
#include "Camera.h"

PatternDuel::PatternDuel(glm::ivec2 initialPos, glm::vec2 initialMovDir, glm::ivec2 entitySize, int speed, TileMap* tileMap) {
    this->pos = initialPos;
    this->movDir = initialMovDir;
    this->entitySize = entitySize;
    this->speed = speed;
    this->map = tileMap;
    movementCounter = 0;
}

glm::ivec2 PatternDuel::calcNewPosition(int deltaTime)
{
    player = Player::getInstance();
    glm::vec2 posPlayer = player->getPosition();

    if (posPlayer.y > pos.y) movDir.y = speed;
    else if (posPlayer.y == pos.y) movDir.y = 0;
    else movDir.y = -speed;

    movementCounter += speed;
    while (movementCounter > 60) {
        movementCounter -= 60;
        if (posPlayer.x > pos.x) movDir.x = speed;
        else movDir.x = -speed;

        if (pos.x - posPlayer.x < 300) movDir.x = speed;
    }

    glm::ivec2 provPosX = pos;
    provPosX.x = pos.x + movDir.x;

    glm::ivec2 provPosY = pos;
    provPosY.y = pos.y + movDir.y;

    // Collisions with the map
    if (map->collisionMoveDown(provPosY, entitySize) || map->collisionMoveUp(provPosY, entitySize))
        movDir.y = 0;

    if ((map->collisionMoveLeft(provPosX, entitySize) || map->collisionMoveRight(provPosX, entitySize)))
        movDir.x *= -1;
    
    // Collisions with the camera
    Camera* cam = Camera::getInstance();
    if (cam->collisionRight(provPosX, entitySize, 0.f) || cam->collisionLeft(provPosX, entitySize, 0.f))
        movDir.x = 0;

    if (cam->collisionDown(provPosY, entitySize, 0.f) || cam->collisionUp(provPosY, entitySize, 0.f))
        movDir.y = 0;
    

    glm::ivec2 newPos;
    newPos.x = pos.x + movDir.x;
    newPos.y = pos.y + movDir.y;

    pos = newPos;
    return newPos;
}
