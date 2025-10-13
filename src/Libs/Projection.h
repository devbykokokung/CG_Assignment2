#ifndef PROJECTION_H
#define PROJECTION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Projection {
public:
    Projection() {
        fov = 45.0f;
        aspectRatio = 800.0f / 600.0f;
        nearPlane = 0.1f;
        farPlane = 100.0f;
        updateProjectionMatrix();
    }

    Projection(float fovDegrees, float aspect, float near, float far) {
        fov = fovDegrees;
        aspectRatio = aspect;
        nearPlane = near;
        farPlane = far;
        updateProjectionMatrix();
    }

    void setFOV(float fovDegrees) {
        fov = fovDegrees;
        updateProjectionMatrix();
    }

    void setAspectRatio(float aspect) {
        aspectRatio = aspect;
        updateProjectionMatrix();
    }

    void setAspectRatio(float width, float height) {
        aspectRatio = width / height;
        updateProjectionMatrix();
    }

    void setNearPlane(float near) {
        nearPlane = near;
        updateProjectionMatrix();
    }

    void setFarPlane(float far) {
        farPlane = far;
        updateProjectionMatrix();
    }

    glm::mat4 getProjectionMatrix() const {
        return projectionMatrix;
    }

private:
    void updateProjectionMatrix() {
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
    glm::mat4 projectionMatrix;
};

#endif