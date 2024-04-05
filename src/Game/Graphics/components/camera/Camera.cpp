//
// Created by janha on 12/03/2024.
//

#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"

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

const glm::vec3 &Camera::getCameraDirection() const {
    return cameraDirection;
}

void Camera::setCameraDirection(const glm::vec3 &cameraDirection) {
    Camera::cameraDirection = cameraDirection;
}

const glm::vec3 &Camera::getCameraTarget() const {
    return cameraTarget;
}

void Camera::setCameraTarget(const glm::vec3 &cameraTarget) {
    Camera::cameraTarget = cameraTarget;
    this->cameraDirection = glm::normalize(cameraPos - cameraTarget);
}

const glm::vec3 &Camera::getCameraRight() const {
    return cameraRight;
}

void Camera::updateCameraRight() {
    this->cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
}

const glm::vec3 &Camera::getCameraUp() const {
    return cameraUp;
}

void Camera::updateCameraUp() {
    this->cameraUp = glm::cross(cameraDirection, cameraRight);
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(cameraPos, cameraTarget, cameraUp);
}

float Camera::getZoom() const {
    return zoom;
}

void Camera::setZoom(float newZoom) {
    this->zoom = newZoom;
}
