#pragma once

#include "entity.h"   
#include "camera.h"   
#include "image.h"    
#include "mesh.h"     
#include "texture.h"

class Entity {
public:
    Entity();
    Entity(Matrix44 modelMatrix);
    Entity(Matrix44 modelMatrix, Mesh mesh);

    void setModelMatrix(Matrix44 modelMatrix);
    void setMesh(Mesh mesh);
    Matrix44 getModelMatrix();
    Mesh getMesh();
    void setTexture(Image t);
    void Render(Image* framebuffer, Camera* camera, const Color& c, bool tecla, FloatImage* zBuffer, float c1, float z1, float t1);
    void Entity::Update(float seconds_elapsed);
    void Entity::setRotate(bool rotate);
    void Entity::setTranslate(bool translate);
    void Entity::setEscalate(bool escalate);
    void Entity::setTranslationSpeed(float value);

private:
    Matrix44 modelMatrix;
    Mesh mesh;
    bool rotate;
    bool translate;
    bool escalate;
    bool scalingUp;
    bool movingUp;
    float translationSpeed;
    Image textura;
};