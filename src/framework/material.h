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
        // La llum la conte el material mm.

};
struct ColorComponents {
    Color Ka;
    Color Kd;
    Color Ks;
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
    Material( Shader* s,  Texture* t,  Color& ka,  Color& kd,  Color& ks, int shininess,  Light& sL);

    void setKa( Color& Kaa);
    void setKd( Color& Kdd);
    void setKs( Color& Kss);
    void setColorComponents( ColorComponents& c);
    void setLight( Light& sLL);
    void setShininess(int Sh);
    void setTexture( Texture* t);
    void setShader( Shader* s);

    void Enable(const sUniformData& uniformData);
    void Disable();
};
