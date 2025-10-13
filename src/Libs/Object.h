#ifndef OBJECT_H
#define OBJECT_H

#include "Mesh.h"
#include "Material.h"

class Object {
public:
    Object() {
        mesh = new Mesh();
    }

    ~Object() {
        delete mesh;
    }

    void loadOBJ(const char* fileLocation) {
        mesh->CreateMeshFromOBJ(fileLocation);
    }

    void createMesh(const GLfloat* vertices,
        const unsigned int* indices,
        unsigned int numOfFloats,
        unsigned int numOfIndices) {
        mesh->CreateMesh(vertices, indices, numOfFloats, numOfIndices);
    }

    Mesh* getMesh() {
        return mesh;
    }

    Material* getMaterial() {
        return material;
    }

    void setMaterial(Material* mat) {
        material = mat;
    }

private:
    Mesh* mesh;
    Material* material;
};

#endif