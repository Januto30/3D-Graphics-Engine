#pragma once

#include "camera.h"
#include "image.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "framework.h"
#include "material.h"


class Entity {
public:
    Entity();
    Entity(Matrix44 modelMatrix);
    Entity(Matrix44 modelMatrix, Mesh mesh);
    Entity(Matrix44 modelMatrix, Mesh mesh, Material* material);

    void setModelMatrix(Matrix44 modelMatrix);
    void setMesh(Mesh mesh);
    Matrix44 getModelMatrix();
    Mesh getMesh();
    void Render(sUniformData uni);

    void Entity::setMaterialTexture(Texture* texture);
    void Entity::Update(float seconds_elapsed);
    void Entity::setRotate(bool rotate);
    void Entity::setTranslate(bool translate);
    void Entity::setEscalate(bool escalate);
    void Entity::setTranslationSpeed(float value);

private:
    Matrix44 modelMatrix;
    Mesh mesh;
    Texture* texture;
    bool rotate;
    bool translate;
    bool escalate;
    bool scalingUp;
    bool movingUp;
    float translationSpeed;
    Material* material;
};

