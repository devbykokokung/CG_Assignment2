#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <functional>
#include "Mesh.h"
#include "Object.h"
#include "Light.h"
#include <glm/glm.hpp>

class World {
public:
    World() {

    }
    ~World() {

    }

    int addObject(Object* obj) {
        objectList.push_back(obj);
        meshList.push_back(obj->getMesh());
        modelMatrices.push_back(glm::mat4(1.0f));
        return meshCount++;
    }

    int addLight(Light* light) {
        lightList.push_back(light);
        return lightCount++;
    }

    Mesh* setTransform(int index, glm::mat4 modelMatrix) {
        if (index < 0 || index >= meshCount) return nullptr;
        if (index >= modelMatrices.size()) {
            modelMatrices.resize(index + 1, glm::mat4(1.0f));
        }
        modelMatrices[index] = modelMatrix;
        return meshList[index];
    }

    Mesh* setTransform(int index, std::function<glm::mat4()> modelMatrixFunc) {
        if (index < 0 || index >= meshCount) return nullptr;
        if (index >= modelMatrices.size()) {
            modelMatrices.resize(index + 1, glm::mat4(1.0f));
        }
        modelMatrices[index] = modelMatrixFunc();
        return meshList[index];
    }

    int getMeshCount() const {
        return meshCount;
    }

    int getLightCount() const {
        return lightCount;
    }

    Mesh* getMesh(int index) {
        if (index < 0 || index >= meshCount) return nullptr;
        return meshList[index];
    }

    Object* getObject(int index) {
        if (index < 0 || index >= meshCount) return nullptr;
        return objectList[index];
    }

    Light* getLight(int index) {
        if (index < 0 || index >= lightCount) return nullptr;
        return lightList[index];
    }

    glm::mat4 getModelMatrix(int index) const {
        // if (index < 0 || index >= modelMatrices.size()) return glm::mat4(1.0f);
        return modelMatrices[index];
    }

private:
    int meshCount = 0;
    int lightCount = 0;
    std::vector<Object*> objectList;
    std::vector<Mesh*> meshList;
    std::vector<Light*> lightList;
    std::vector<glm::mat4> modelMatrices;
};

#endif