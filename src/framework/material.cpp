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
    this->components.Ka = 0;
    this->components.Kd = 0;
    this->components.Ks = 0;
    this->Shininess = 0;
}

Material::Material(const Shader& s, const Texture& t, const Color& ka, const Color& kd, const Color& ks, int shininess, const Light& sL) {
    this->components.Ka = ka;
    this->components.Kd = kd;
    this->components.Ks = ks;

    this->Shininess = shininess;
    this->shader = s;
    this->texture = t;
    this->sLight = sL; 
}

void Material::setKa(const Color& Kaa) {
    this->components.Ka = Kaa;
}

void Material::setKd(const Color& Kdd) {
    this->components.Kd = Kdd;
}

void Material::setKs(const Color& Kss) {
    this->components.Ks = Kss;
}

void Material::setColorComponents(const ColorComponents& c) {
    this->components = c;
}

void Material::setLight(const Light& sLL) {
    this->sLight = sLL;
}

void Material::setShininess(int Sh) {
    this->Shininess = Sh;
}

void Material::setTexture(const Texture& t) {
    this->texture = t;
}

void Material::setShader(const Shader& s) {
    this->shader = s;
}



// Método para habilitar el shader y pasar los datos uniformes
void Material::Enable(const sUniformData& uniformData){
    shader.Enable();
    uniformData.projectioViewMatrix
    //this->components = uniformData.mm.components;
    //this->shader = uniformData.mm.shader;
    //this->Shininess = uniformData.mm.Shininess;
    //this->sLight = uniformData.mm.sLight;
    //this->texture = uniformData.mm.texture;
}

// Método para deshabilitar el shader
void Material::Disable() {
    // Llamadas al shader para deshabilitarlo
    this->shader.Disable();
}

