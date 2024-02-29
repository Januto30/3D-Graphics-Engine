#include <cstring>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <iostream>

#include "framework.h"
#include "light.h"


Light::Light() {
	this->position = Vector3(0.0f, 0.0f, 0.0f);
	this->IComp.Id = 0;
	this->IComp.Is = 0;
}

Light::Light(const Vector3& pos, int diffuseIntensity, int specularIntensity) {
	this->IComp.Id = diffuseIntensity;
	this->IComp.Is = specularIntensity;

	this->position = pos;
}


