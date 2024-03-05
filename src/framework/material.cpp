#include "material.h"
#include <cstring>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "framework.h"
#include "texture.h"
#include "shader.h"
#include "entity.h"

Material::Material() {
    this->components.Ka = 1;
    this->components.Kd = 1;
    this->components.Ks = 1;
    this->Shininess = 1;
}
 
Material::Material( Shader* s,  Texture* t, Vector3& ka, Vector3& kd, Vector3& ks, int shininess,  Light& sL){
    this->components.Ka = ka;
    this->components.Kd = kd;
    this->components.Ks = ks;

    this->Shininess = shininess;
    this->shader = s;
    this->texture = t;
    this->sLight = sL; 
}

Vector3 Material::getKa() {
    return this->components.Ka;
}

Vector3 Material::getKd() {
    return this->components.Kd;
}

Vector3 Material::getKs() {
    return this->components.Ks;
}


void Material::setKa(Vector3& Kaa) {
    this->components.Ka = Kaa;
}

void Material::setKd(Vector3& Kdd) {
    this->components.Kd = Kdd;
}

void Material::setKs( Vector3& Kss) {
    this->components.Ks = Kss;
}

void Material::setColorComponents( ColorComponents& c) {
    this->components = c;
}

void Material::setLight( Light& sLL) {
    this->sLight = sLL;
}

void Material::setShininess(int Sh) {
    this->Shininess = Sh;
}

void Material::setTexture( Texture* t) {
    this->texture = t;
}

void Material::setShader( Shader* s) {
    this->shader = s;
}

void Material::Enable(const sUniformData& uniformData) {
    //Trucada al shader per habilitar-lo
    shader->Enable();

    //Passem les variables neessaries a la GPU des de la Uniform Data
    shader->SetTexture("u_normal_map", uniformData.tt);
    shader->SetVector3("v_Ka", uniformData.Ka);
    shader->SetVector3("v_Kd", uniformData.Kd);
    shader->SetVector3("v_Ks", uniformData.Ks);
    shader->SetMatrix44("u_model", uniformData.modelMatrixx);
    shader->SetMatrix44("u_viewprojection", uniformData.cc->GetViewProjectionMatrix());
    shader->SetTexture("u_face_texture", uniformData.tt);
    shader->SetVector3("u_lightPosition", uniformData.ll_pos);
    shader->SetVector3("u_lightColor", uniformData.color);
    shader->SetFloat("let_c", uniformData.let_c);


};


void Material::Disable() {
    //Trucada al shader per deshabilitar-lo
    shader->Disable();
}

