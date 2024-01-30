#include "entity.h"
#include "mesh.h"
#include "image.h"
#include <cstring> 

Entity::Entity() {
    modelMatrix.SetIdentity();
    this->mesh = mesh;
}

Entity::Entity(Matrix44 modelMatrix) {
    setModelMatrix(modelMatrix);
}

Entity::Entity(Matrix44 modelMatrix, Mesh mesh) {
    setModelMatrix(modelMatrix);
}

void Entity::setModelMatrix(Matrix44 modelMatrix) {
    this->modelMatrix = modelMatrix;
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

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
    const std::vector<Vector3>& meshVertices = mesh.GetVertices();

    for (size_t i = 0; i < meshVertices.size(); i += 3) {
        Vector3 vec1;
        Vector3 vec2;
        Vector3 vec3;

        //PAS 1: LOCAL SPACE TO WORLD SPACE -------------------------------------------------------------------------------
        vec1 = modelMatrix * mesh.GetVertices()[i];
        vec2 = modelMatrix * mesh.GetVertices()[i+1];
        vec3 = modelMatrix * mesh.GetVertices()[i+2];
        //-----------------------------------------------------------------------------------------------------------------
        
        //PAS 2: WORLD SPACE TO VIEW SPACE TO CLIP SPACE ------------------------------------------------------------------
        bool negZ0, negZ1, negZ2;
        Vector3 clipPos0 = camera->ProjectVector(vec1, negZ0);
        Vector3 clipPos1 = camera->ProjectVector(vec2, negZ1);
        Vector3 clipPos2 = camera->ProjectVector(vec3, negZ2);

        //Check if any vertex is outside the camera frustum
        if (negZ0 || negZ1 || negZ2) {
            continue;  // Skip this triangle
        }
        //-----------------------------------------------------------------------------------------------------------------

        //PAS 3:CLIP SPACE TO SCREEN SPACE ----------------------------------------------------------------------------------
        int Width = framebuffer->width;
        int Height = framebuffer->height;
        Vector2 screenPos0 = Vector2((clipPos0.x + 1.0f) * 0.5f * Width, (clipPos0.y + 1.0f) * 0.5f * Height);
        Vector2 screenPos1 = Vector2((clipPos1.x + 1.0f) * 0.5f * Width, (clipPos1.y + 1.0f) * 0.5f * Height);
        Vector2 screenPos2 = Vector2((clipPos2.x + 1.0f) * 0.5f * Width, (clipPos2.y + 1.0f) * 0.5f * Height);

        // Draw lines using your DrawLineDDA function
        framebuffer->DrawLineDDA(screenPos0.x, screenPos0.y, screenPos1.x, screenPos1.y, c);
        framebuffer->DrawLineDDA(screenPos1.x, screenPos1.y, screenPos2.x, screenPos2.y, c);
        framebuffer->DrawLineDDA(screenPos2.x, screenPos2.y, screenPos0.x, screenPos0.y, c);   
    }
}

