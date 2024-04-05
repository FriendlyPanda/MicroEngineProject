//
// Created by janha on 12/03/2024.
//

#ifndef MEP_CAMERA_H
#define MEP_CAMERA_H


#include "glm/glm.hpp"

class Camera {
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraDirection;
    glm::vec3 cameraTarget;
    glm::vec3 cameraRight;
    glm::vec3 cameraUp;
    float zoom = 45.0f;

public:
    Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget);

    glm::vec3 getPosition();
    void setPosition(glm::vec3 newPosition);

    [[nodiscard]] const glm::vec3 &getCameraDirection() const;
    void setCameraDirection(const glm::vec3 &cameraDirection);

    [[nodiscard]] const glm::vec3 &getCameraTarget() const;
    void setCameraTarget(const glm::vec3 &cameraTarget);

    [[nodiscard]] const glm::vec3 &getCameraRight() const;
    void updateCameraRight();

    [[nodiscard]] const glm::vec3 &getCameraUp() const;
    void updateCameraUp();

    glm::mat4 getViewMatrix();

    float getZoom() const;
    void setZoom(float newZoom);
};


#endif //MEP_CAMERA_H
