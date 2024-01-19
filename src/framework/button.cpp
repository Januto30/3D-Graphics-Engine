#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "GL/glew.h"
#include "../extra/picopng.h"
#include "image.h"
#include "utils.h"
#include "camera.h"
#include "mesh.h"
#include <cmath>
#include "button.h"

class Button {
private:
    Image buttonImage;
    Vector2 position;

public:
    Button(const Image& image, const Vector2& position) : buttonImage(image), position(position) {}

    bool IsMouseInside(const Vector2& mousePosition) const {
        printf("xd");
        return (mousePosition.x >= position.x && mousePosition.x <= position.x + buttonImage.width &&
            mousePosition.y >= position.y && mousePosition.y <= position.y + buttonImage.height);
    }

};