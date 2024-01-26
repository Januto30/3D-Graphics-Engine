#pragma once

#include "mesh.h"  

class Entity {
public:

    Entity();
    Entity(const glm::mat4& modelMatrix);
    Entity(const glm::mat4& modelMatrix, Mesh mesh);

    const glm::mat4& getModelMatrix() const;

    void setModelMatrix(const glm::mat4& modelMatrix);

    const Mesh& getMesh() const;

    void setMesh(const Mesh& mesh);

private:
    glm::mat4 modelMatrix;
    Mesh mesh;
};

