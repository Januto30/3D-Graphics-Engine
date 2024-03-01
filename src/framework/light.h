#ifndef LIGHT_H
#define LIGHT_H


#include "framework.h"

class Light {
    Vector3 position;

    struct Intensities {
        Vector3 Id;
        Vector3 Is;
    } IComp;

public:
    // Constructors
    Light();
    Light(const Vector3& pos, Vector3 diffuseIntensity, Vector3 specularIntensity);
};

#endif // LIGHT_H
