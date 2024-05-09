//
// Created by janha on 12/03/2024.
// Documentation Generated by Jetbrains AI
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
    /**
     * a simple camera constructor
     * @param cameraPos the position of the camera
     * @param cameraTarget the 3D point to focus the camera on
     */
    Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget);

    /**
     * Get the camera position
     * @return camera position point
     */
    glm::vec3 getPosition();

    /**
     * Set the camera position
     * @param newPosition new camera position point
     */
    void setPosition(glm::vec3 newPosition);

    /**
     * get the camera position in vec3
     * @return camera rotation
     */
    [[nodiscard]] const glm::vec3 &getCameraDirection() const;

    /**
     * Set the camera rotation
     * @param cameraDirection set the camera rotation in vec3
     */
    void setCameraDirection(const glm::vec3 &cameraDirection);

    /**
     * @brief Get the camera target position.
     *
     * This function returns the camera target position, which is the 3D point
     * that the camera is focused on.
     *
     * @return const glm::vec3& The camera target position.
     */
    [[nodiscard]] const glm::vec3 &getCameraTarget() const;
    /**
     * @brief Sets the target to which the camera will be focused.
     *
     * This function sets the camera target, which is the 3D point the camera is directed towards.
     * It updates the camera direction accordingly.
     *
     * @param cameraTarget The target point to focus the camera on.
     */
    void setCameraTarget(const glm::vec3 &cameraTarget);

    /**
     * @brief Get the right vector of the camera.
     *
     * @return const glm::vec3& The right vector of the camera.
     */
    [[nodiscard]] const glm::vec3 &getCameraRight() const;
    /**
     * @brief Update the camera's right vector based on the camera's direction.
     *
     * This function updates the camera's right vector by taking the cross product of the world up vector (0, 1, 0)
     * and the camera's direction vector. The result is then normalized to ensure it has unit length.
     *
     * @note This function should be called whenever the camera's direction vector changes.
     */
    void updateCameraRight();

    /**
     * @brief Get the up vector of the camera.
     *
     * @return const glm::vec3& The up vector of the camera.
     *
     * This method returns the up vector of the camera. The up vector
     * defines the direction that is considered "up" from the camera's
     * perspective. The returned value is of type glm::vec3, which is a
     * vector of 3 single-precision floating-point numbers.
     */
    [[nodiscard]] const glm::vec3 &getCameraUp() const;
    /**
     * Updates the camera's upward vector based on the current camera direction and right vectors.
     * This function calculates the cross product of the camera direction and right vectors to determine the updated upward vector.
     */
    void updateCameraUp();

    /**
     * @brief Returns the view matrix of the camera.
     *
     * This function calculates and returns the view matrix of the camera using the camera position, target, and up vectors.
     * The view matrix is a 4x4 matrix that represents the transformation from world coordinates to camera coordinates.
     *
     * @return The view matrix of the camera as a glm::mat4.
     */
    glm::mat4 getViewMatrix();

    /**
     * @brief Get the current zoom level of the camera.
     *
     * @return The zoom level as a floating point value.
     */
    float getZoom() const;
    /**
     * @brief Set the zoom level of the camera.
     *
     * This function allows you to set the zoom level of the camera. The zoom level determines the field of view of the camera, which affects the apparent size of objects in the scene.
     *
     * @param newZoom The new zoom level to set. The zoom level should be a positive floating-point value.
     */
    void setZoom(float newZoom);
};


#endif //MEP_CAMERA_H
