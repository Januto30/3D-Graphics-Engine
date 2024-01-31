#pragma once

#include "entity.h"   
#include "camera.h"   
#include "image.h"    
#include "mesh.h"     

class Entity {
public:
    Entity();
    Entity(Matrix44 modelMatrix);
    Entity(Matrix44 modelMatrix, Mesh mesh);

    void setModelMatrix(Matrix44 modelMatrix);
    void setMesh(Mesh mesh);
    Matrix44 getModelMatrix();
    Mesh getMesh();
    void Render(Image* framebuffer, Camera* camera, const Color& c);
    void Entity::Update(float seconds_elapsed);

private:
    Matrix44 modelMatrix;  
    Mesh mesh;
};