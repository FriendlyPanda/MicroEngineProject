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

public:
    Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget);

    glm::vec3 getPosition();
    void setPosition(glm::vec3 newPosition);
};


#endif //MEP_CAMERA_H
