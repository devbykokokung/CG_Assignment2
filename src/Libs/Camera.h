#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    Camera() {
        position = glm::vec3(0.0f, 0.0f, 5.0f);
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw = -90.0f;
        pitch = 0.0f;
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        
        movementSpeed = 2.5f;
        turnSpeed = 0.1f;
        
        update();
    }

    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) {
        position = startPosition;
        worldUp = startUp;
        yaw = startYaw;
        pitch = startPitch;
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        
        movementSpeed = startMoveSpeed;
        turnSpeed = startTurnSpeed;
        
        update();
    }

    void keyControl(bool* keys, GLfloat deltaTime) {
        GLfloat velocity = movementSpeed * deltaTime;

        if (keys[GLFW_KEY_W])
        {
            position += front * velocity;
        }

        if (keys[GLFW_KEY_S])
        {
            position -= front * velocity;
        }

        if (keys[GLFW_KEY_A])
        {
            position -= right * velocity;
        }

        if (keys[GLFW_KEY_D])
        {
            position += right * velocity;
        }

        if (keys[GLFW_KEY_P])
        {
            printf("Camera Position: (%.2f, %.2f, %.2f)\n", position.x, position.y, position.z);
            printf("Up Vector: (%.2f, %.2f, %.2f)\n", up.x, up.y, up.z);
            printf("Yaw: %.2f degrees\n", yaw);
            printf("Pitch: %.2f degrees\n", pitch);
            printf("Movement Speed: %.2f\n", movementSpeed);
            printf("Turn Speed: %.2f\n", turnSpeed);
        }
    }

    void mouseControl(GLfloat xChange, GLfloat yChange) {
        xChange *= turnSpeed;
        yChange *= turnSpeed;

        yaw += xChange;
        pitch += yChange;

        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }

        if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }

        update();
    }

    glm::vec3 getPosition() const {
        return position;
    }

    glm::vec3 getDirection() const {
        return glm::normalize(front);
    }

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

    void setPosition(glm::vec3 pos) {
        position = pos;
    }

    void setTarget(glm::vec3 tgt) {
        front = glm::normalize(tgt - position);
    }

    void setUpVector(glm::vec3 upVec) {
        worldUp = upVec;
        update();
    }

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat movementSpeed;
    GLfloat turnSpeed;

    void update() {
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
};

#endif