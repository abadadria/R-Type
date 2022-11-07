#include "Camera.h"

Camera* Camera::instance{ nullptr };

Camera::Camera() {}

Camera::~Camera() {
    delete instance;
}

Camera* Camera::getInstance() {
    if (instance == nullptr) {
        instance = new Camera();
    }
    return instance;
}

void Camera::init(glm::vec2 pos, glm::vec2 size, glm::vec2 speed) {
    cameraPos = pos;
    cameraSize = size;
    cameraSpeed = speed;
}

glm::mat4 Camera::update() {
    cameraPos += cameraSpeed;
    return glm::ortho(cameraPos.x, cameraPos.x + cameraSize.x, cameraPos.y + cameraSize.y, cameraPos.y);
}

glm::vec2 Camera::getPos() const {
    return cameraPos;
}

glm::vec2 Camera::getSize() const {
    return cameraSize;
}

glm::vec2 Camera::getSpeed() const {
    return cameraSpeed;
}

void Camera::setPos(glm::vec2 pos) {
    cameraPos = pos;
}

void Camera::setSpeed(glm::vec2 speed) {
    cameraSpeed = speed;
}

bool Camera::collisionUp(glm::vec2 entityPos, glm::vec2 entitySize, float margin) const {
    return entityPos.y <= (cameraPos.y - margin);
}

bool Camera::collisionDown(glm::vec2 entityPos, glm::vec2 entitySize, float margin) const {
    return entityPos.y + entitySize.y >= (cameraPos.y + cameraSize.y + margin - 32.f);
}

bool Camera::collisionLeft(glm::vec2 entityPos, glm::vec2 entitySize, float margin) const {
    return entityPos.x <= (cameraPos.x - margin);
}

bool Camera::collisionRight(glm::vec2 entityPos, glm::vec2 entitySize, float margin) const {
    return entityPos.x + entitySize.x >= (cameraPos.x + cameraSize.x + margin);
}

bool Camera::inFrameUp(glm::vec2 entityPos, glm::vec2 entitySize) const {
    return entityPos.y + entitySize.y > (cameraPos.y);
}

bool Camera::inFrameDown(glm::vec2 entityPos, glm::vec2 entitySize) const {
    return entityPos.y < (cameraPos.y + cameraSize.y - 32.f);
}

bool Camera::inFrameLeft(glm::vec2 entityPos, glm::vec2 entitySize) const {
    return entityPos.x + entitySize.x > (cameraPos.x);
}

bool Camera::inFrameRight(glm::vec2 entityPos, glm::vec2 entitySize) const {
    return entityPos.x < (cameraPos.x + cameraSize.x);
}

bool Camera::inFrame(glm::vec2 entityPos, glm::vec2 entitySize) const
{
    return
        inFrameRight(entityPos, entitySize) ||
        inFrameLeft(entityPos, entitySize) ||
        inFrameDown(entityPos, entitySize) ||
        inFrameUp(entityPos, entitySize);
}

bool Camera::collision(glm::vec2 entityPos, glm::vec2 entitySize, float margin) const {
    return
        collisionRight(entityPos, entitySize, margin) ||
        collisionLeft(entityPos, entitySize, margin)  ||
        collisionDown(entityPos, entitySize, margin)  ||
        collisionUp(entityPos, entitySize, margin);
}
