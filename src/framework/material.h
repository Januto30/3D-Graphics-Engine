#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "framework.h"
#include "texture.h"
#include "shader.h"
#include "light.h"
#include "camera.h"


struct ColorComponents {
    Color Ka;
    Color Kd;
    Color Ks;
};


class Material {
    Shader shader;
    Texture texture;
    int Shininess;
    Light sLight;
    ColorComponents components;


public:
    // Constructor with parameters
    Material();
    Material(const Shader& s, const Texture& t, const Color& ka, const Color& kd, const Color& ks, int shininess, const Light& sL);

    void setKa(const Color& Kaa);
    void setKd(const Color& Kdd);
    void setKs(const Color& Kss);
    void setColorComponents(const ColorComponents& c);
    void setLight(const Light& sLL);
    void setShininess(int Sh);
    void setTexture(const Texture& t);
    void setShader(const Shader& s);

    void Enable();
    void Disable();
};

typedef struct sUniformData {
    Camera cc;
    Material mm;
    // La llum la conte el material mm.

};