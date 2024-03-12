//
// Created by janha on 12/03/2024.
//

#include "Camera.h"

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget) {
    this->cameraPos = cameraPos;
    this->cameraTarget = cameraTarget;
    this->cameraDirection = glm::normalize(cameraPos - cameraTarget);
    this->cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
    this->cameraUp = glm::cross(cameraDirection, cameraRight);
}

glm::vec3 Camera::getPosition() {
    return cameraPos;
}

void Camera::setPosition(glm::vec3 newPosition) {
    cameraPos = newPosition;
}
