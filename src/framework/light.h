#ifndef LIGHT_H
#define LIGHT_H


#include "framework.h"

class Light {
    Vector3 position;

    struct Intensities {
        int Id;
        int Is;
    } IComp;

public:
    // Constructors
    Light();
    Light(const Vector3& pos, int diffuseIntensity, int specularIntensity);
};

#endif // LIGHT_H
