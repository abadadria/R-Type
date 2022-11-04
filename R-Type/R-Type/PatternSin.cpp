#include "PatternSin.h"

PatternSin::PatternSin(glm::ivec2 initialPos, int initialAngle, int angleStep, int xSpeed, int amplitude) {
    this->pos = initialPos;
    this->currentAngle = initialAngle;
    this->angleStep = angleStep;
    this->xSpeed = xSpeed;
    this->amplitude = amplitude;
}

glm::ivec2 PatternSin::calcNewPosition(int deltaTime)
{
    glm::ivec2 newPos;
    currentAngle += angleStep;
    newPos.x = pos.x = pos.x + xSpeed;
    newPos.y = int(pos.y + (amplitude / 2.f) * sin(3.14159f * currentAngle / 180.f));
    return newPos;
}
