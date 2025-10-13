#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
    Light() {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        colour = glm::vec3(1.0f, 1.0f, 1.0f);
        intensity = 1.0f;
    }

    Light(glm::vec3 pos, glm::vec3 col, float inten = 1.0f) {
        position = pos;
        colour = col;
        intensity = inten;
    }

    void setPosition(glm::vec3 pos) {
        position = pos;
    }

    void setColour(glm::vec3 col) {
        colour = col;
    }

    void setIntensity(float inten) {
        intensity = inten;
    }

    glm::vec3 getPosition() const {
        return position;
    }

    glm::vec3 getColour() const {
        return colour * intensity;
    }

    glm::vec3 getRawColour() const {
        return colour;
    }

    float getIntensity() const {
        return intensity;
    }

private:
    glm::vec3 position;
    glm::vec3 colour;
    float intensity;
};

#endif
