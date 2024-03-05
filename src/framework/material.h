#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "framework.h"
#include "texture.h"
#include "shader.h"
#include "light.h"
#include "camera.h"

struct sUniformData {
    Matrix44 projectioViewMatrix;
    Matrix44 modelMatrixx;
    Texture* tt;
    Camera* cc;
    Vector3 ll_pos;
    Vector3 color;
    Vector3 Ka;
    Vector3 Kd;
    Vector3 Ks;
    float let_c;

};

struct ColorComponents {
    Vector3 Ka;
    Vector3 Kd;
    Vector3 Ks;
};


class Material {
    Shader *shader;

    Texture *texture;
    int Shininess;
    Light sLight;
    ColorComponents components;


public:
    // Constructor with parameters
    Material();
    Material( Shader* s,  Texture* t, Vector3& ka, Vector3& kd, Vector3& ks, int shininess,  Light& sL);

    Vector3 getKa();
    Vector3 getKs();
    Vector3 getKd();


    void setKa(Vector3& Kaa);
    void setKd(Vector3& Kdd);
    void setKs(Vector3& Kss);
    void setColorComponents( ColorComponents& c);
    void setLight( Light& sLL);
    void setShininess(int Sh);
    void setTexture( Texture* t);
    void setShader( Shader* s);

    void Enable(const sUniformData& uniformData);
    void Disable();
};
