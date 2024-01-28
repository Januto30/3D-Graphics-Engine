#pragma once

#include "entity.h"   
#include "camera.h"   
#include "image.h"    
#include "mesh.h"     

class Entity {
public:
    Entity();
    Entity(float* modelMatrix);
    Entity(float* modelMatrix, Mesh* mesh);

    void setModelMatrix(float* modelMatrix);
    void setMesh(Mesh* mesh);
    const float* getModelMatrix() const;
    Mesh* getMesh() const;
    void Render(Image* framebuffer, Camera* camera, const Color& c);


private:
    float modelMatrix[16];  
    Mesh* mesh;
};