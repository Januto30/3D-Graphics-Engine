#include "entity.h"
#include "mesh.h"
#include "image.h"
#include <cstring> 

Entity::Entity() {
    modelMatrix.SetIdentity();
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

void Entity::setMesh(Mesh* mesh) {
    this->mesh = mesh;
}

Matrix44 Entity::getModelMatrix() {
    return modelMatrix;
}

Mesh* Entity::getMesh() const {
    return mesh;
}

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
    const std::vector<Vector3>& meshVertices = mesh->GetVertices();
    std::vector<Vector3> LlistaVec;

    for (size_t i = 0; i < meshVertices.size(); i += 3) {
        LlistaVec[i] = operator*(modelMatrix, mesh->GetVertices()[i]);
        LlistaVec[i+1] = operator*(modelMatrix, mesh->GetVertices()[i]);
        LlistaVec[i+2] = operator*(modelMatrix, mesh->GetVertices()[i]);


        //PAS 3: WORLD SPACE TO VIEW SPACE TO CLIP SPACE ------------------------------------------------------------------
        bool negZ0, negZ1, negZ2;
        Vector3 clipPos0 = camera->ProjectVector((LlistaVec[i].x, LlistaVec[i].y, LlistaVec[i].z), negZ0);
        Vector3 clipPos1 = camera->ProjectVector((LlistaVec[i + 1].x, LlistaVec[i + 1].y, LlistaVec[i + 1].z), negZ1);
        Vector3 clipPos2 = camera->ProjectVector((LlistaVec[i + 2].x, LlistaVec[i + 2].y, LlistaVec[i + 2].z), negZ2);

        //Check if any vertex is outside the camera frustum
        if (negZ0 || negZ1 || negZ2) {
            continue;  // Skip this triangle
        }
        //-----------------------------------------------------------------------------------------------------------------

        //PAS 4:CLIP SPACE TO SCREEN SPACE ----------------------------------------------------------------------------------
        int screenWidth = framebuffer->width;
        int screenHeight = framebuffer->height;
        Vector2 screenPos0 = Vector2((clipPos0.x + 1.0f) * 0.5f * screenWidth, (1.0f - clipPos0.y) * 0.5f * screenHeight);
        Vector2 screenPos1 = Vector2((clipPos1.x + 1.0f) * 0.5f * screenWidth, (1.0f - clipPos1.y) * 0.5f * screenHeight);
        Vector2 screenPos2 = Vector2((clipPos2.x + 1.0f) * 0.5f * screenWidth, (1.0f - clipPos2.y) * 0.5f * screenHeight);

        // Draw lines using your DrawLineDDA function
        framebuffer->DrawLineDDA(screenPos0.x, screenPos0.y, screenPos1.x, screenPos1.y, c);
        framebuffer->DrawLineDDA(screenPos1.x, screenPos1.y, screenPos2.x, screenPos2.y, c);
        framebuffer->DrawLineDDA(screenPos2.x, screenPos2.y, screenPos0.x, screenPos0.y, c);
    }

}

/*
//Agafem 3 punts amb les seves cordenades (x,y,z,v = 1.0f).
//Per tant tindrem 3 punts de 4 components cada una.

for (size_t i = 0; i < meshVertices.size(); i += 3) {
    //PAS 1: LOCAL SPACE ----------------------------------------------------------------------------------------------
    Vector4 p0 = Vector4(meshVertices[i].x, meshVertices[i].y, meshVertices[i].z, 1.0f);
    Vector4 p1 = Vector4(meshVertices[i + 1].x, meshVertices[i + 1].y, meshVertices[i + 1].z, 1.0f);
    Vector4 p2 = Vector4(meshVertices[i + 2].x, meshVertices[i + 2].y, meshVertices[i + 2].z, 1.0f);
    Vector4 p3 = Vector4(0.f, 0.f, 0.f, 1.0f);

    //-----------------------------------------------------------------------------------------------------------------

//PAS 2: LOCAL SPACE TO WORLD SPACE -------------------------------------------------------------------------------
    Vector4 pw1, pw2, pw3, pw0;

    //Punt 1 en World Space
    pw1.x = modelMatrix[0] * p0.x + modelMatrix[1] * p1.x + modelMatrix[2] * p2.x + modelMatrix[3] * 0;
    pw1.y = modelMatrix[0] * p0.y + modelMatrix[1] * p1.y + modelMatrix[2] * p2.y + modelMatrix[3] * 0;
    pw1.z = modelMatrix[0] * p0.z + modelMatrix[1] * p1.z + modelMatrix[2] * p2.z + modelMatrix[3] * 0;
    pw1.w = modelMatrix[0] * p0.w + modelMatrix[1] * p1.w + modelMatrix[2] * p2.w + modelMatrix[3] * 0;

    //Punt 2 en World Space
    pw2.x = modelMatrix[4] * p0.x + modelMatrix[5] * p1.x + modelMatrix[6] * p2.x + modelMatrix[7] * 0;
    pw2.y = modelMatrix[4] * p0.y + modelMatrix[5] * p1.y + modelMatrix[6] * p2.y + modelMatrix[7] * 0;
    pw2.z = modelMatrix[4] * p0.z + modelMatrix[5] * p1.z + modelMatrix[6] * p2.z + modelMatrix[7] * 0;
    pw2.w = modelMatrix[4] * p0.w + modelMatrix[5] * p1.w + modelMatrix[6] * p2.w + modelMatrix[7] * 0;

    //Punt 3 en World Space
    pw3.x = modelMatrix[8] * p0.x + modelMatrix[9] * p1.x + modelMatrix[10] * p2.x + modelMatrix[11] * 0;
    pw3.y = modelMatrix[8] * p0.y + modelMatrix[9] * p1.y + modelMatrix[10] * p2.y + modelMatrix[11] * 0;
    pw3.z = modelMatrix[8] * p0.z + modelMatrix[9] * p1.z + modelMatrix[10] * p2.z + modelMatrix[11] * 0;
    pw3.w = modelMatrix[8] * p0.w + modelMatrix[9] * p1.w + modelMatrix[10] * p2.w + modelMatrix[11] * 0;

    //Punt 0 en World Space
    pw0.x = modelMatrix[12] * p0.x + modelMatrix[13] * p1.x + modelMatrix[14] * p2.x + modelMatrix[15] * 0;
    pw0.y = modelMatrix[12] * p0.y + modelMatrix[13] * p1.y + modelMatrix[14] * p2.y + modelMatrix[15] * 0;
    pw0.z = modelMatrix[12] * p0.z + modelMatrix[13] * p1.z + modelMatrix[14] * p2.z + modelMatrix[15] * 0;
    pw0.w = modelMatrix[12] * p0.w + modelMatrix[13] * p1.w + modelMatrix[14] * p2.w + modelMatrix[15] * 0;
    //-----------------------------------------------------------------------------------------------------------------
    */