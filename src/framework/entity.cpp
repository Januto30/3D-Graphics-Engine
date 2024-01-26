

#include "entity.h"

Entity::Entity() : modelMatrix(glm::mat4(1.0)), mesh(Mesh()) {}

Entity::Entity(const glm::mat4& modelMatrix) : modelMatrix(modelMatrix), mesh(Mesh()) {}

Entity::Entity(const glm::mat4& modelMatrix, Mesh mesh) : modelMatrix(modelMatrix), mesh(mesh) {}

const glm::mat4& Entity::getModelMatrix() const {
    return modelMatrix;
}

void Entity::setModelMatrix(const glm::mat4& modelMatrix) {
    this->modelMatrix = modelMatrix;
}

const Mesh& Entity::getMesh() const {
    return mesh;
}

void Entity::setMesh(const Mesh& mesh) {
    this->mesh = mesh;
}
