#include "entity.h"
#include "mesh.h"
#include "image.h"
#include <cstring> 
#include "material.h"


Entity::Entity() {
    modelMatrix.SetIdentity();
    this->mesh = mesh;
    this->translate = false;
    this->rotate = false;
    this->escalate = false;
    this->scalingUp = true;
    this->movingUp = true;

}

Entity::Entity(Matrix44 modelMatrix) {
    setModelMatrix(modelMatrix);
}

Entity::Entity(Matrix44 modelMatrix, Mesh mesh) {
    setModelMatrix(modelMatrix);
}

Entity::Entity(Matrix44 modelMatrix, Mesh mesh, Material *material) {
    setModelMatrix(modelMatrix);
    this->mesh = mesh;
    this->material = material;

}

void Entity::setModelMatrix(Matrix44 modelMatrix) {
    this->modelMatrix = modelMatrix;
}

void Entity::setMaterialTexture(Texture* texture) {
    this->material->setTexture(texture);
}

void Entity::setMesh(Mesh mesh) {
    this->mesh = mesh;
}

Matrix44 Entity::getModelMatrix() {
    return modelMatrix;
}

Mesh Entity::getMesh() {
    return mesh;
}

void Entity::setRotate(bool rotate) {
    this->rotate = rotate;
}

void Entity::setTranslate(bool translate) {
    this->translate = translate;
}

void Entity::setEscalate(bool escalate) {
    this->escalate = escalate;
}

void Entity::setTranslationSpeed(float value) {
    this->translationSpeed = value;
}

void Entity::Render(sUniformData uni) {
    glEnable(GL_DEPTH_TEST);
    material->Enable(uni);
    mesh.Render();
    material->Disable();
}

