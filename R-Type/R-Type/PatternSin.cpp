#include "PatternSin.h"

PatternSin::PatternSin(int initialAngle, int angleStep, int xSpeed, int amplitude) {
    this->initialAngle = initialAngle;
    this->angleStep = angleStep;
    this->xSpeed = xSpeed;
    this->amplitude = amplitude;
}

glm::ivec2 PatternSin::calcNewPosition(int deltaTime, glm::ivec2 currentPos)
{
    glm::ivec2 newPos;
    currentAngle += angleStep;
    newPos.x = currentPos.x + xSpeed;
    newPos.y = int(currentPos.y - amplitude / 2.f * sin(3.14159f * currentAngle / 180.f));
    return glm::ivec2();
}
