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

Entity::Entity(Matrix44 modelMatrix, Mesh mesh, Texture* texture, Shader* shader, Material material) {
    setModelMatrix(modelMatrix);
    this->texture = texture;
    this->shader = shader;
    this->mesh = mesh;
    this->material = material;
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
    shader->Enable();
    shader->SetMatrix44("u_model", modelMatrix);
    shader->SetMatrix44("u_viewprojection", uni.cc.viewprojection_matrix);
    shader->SetTexture("u_face_texture", texture);
    mesh.Render();
    shader->Disable();
}


void Entity::Update(float seconds_elapsed) {
    if (rotate == true) {
        Vector3 rotation_axis(0.0f, 1.0f, 0.0f);
        modelMatrix.RotateLocal(seconds_elapsed * (PI / 10.0f), rotation_axis);
    }
    if (escalate == true) {
        if (scalingUp) {
            if (modelMatrix._11 < 2.0f) {
                modelMatrix._11 += seconds_elapsed;
                modelMatrix._22 += seconds_elapsed;
                modelMatrix._33 += seconds_elapsed;
            }
            else {
                scalingUp = false;
            }
        }
        else {
            if (modelMatrix._11 > 0.3f) {
                modelMatrix._11 -= seconds_elapsed;
                modelMatrix._22 -= seconds_elapsed;
                modelMatrix._33 -= seconds_elapsed;
            }
            else {
                scalingUp = true;
            }
        }
    }
    if (translate) {
        float translationDistance = translationSpeed * seconds_elapsed;

        if (movingUp) {
            modelMatrix.Translate(0.0f, translationDistance, 0.0f);
        }
        else {
            modelMatrix.Translate(0.0f, -translationDistance, 0.0f);
        }
        if (modelMatrix.GetTranslation().y >= 0.3f) {
            movingUp = false;
        }
        else if (modelMatrix.GetTranslation().y <= -0.2f) {
            movingUp = true;
        }
    }
}
