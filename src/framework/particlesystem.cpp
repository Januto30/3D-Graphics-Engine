/*
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
#include "image.h"
#include "particlesystem.h"

float RandomFloat(float min, float max) {
    return min + (max - min) * rand() / (RAND_MAX + 1.0f);
}

void ParticleSystem::Init(unsigned int width, unsigned int height) {
    // Inicializar las partículas en posiciones aleatorias

    for (int i = 0; i < MAX_PARTICLES; ++i) {
        particles[i].position = Vector2(RandomFloat(0.0f, width), RandomFloat(0.0f, height));
        particles[i].velocity = Vector2(RandomFloat(0.0f, width), RandomFloat(0.0f, height));
        particles[i].color = Color(rand() * 255, rand() * 255, rand() * 255);
        particles[i].acceleration = RandomFloat(-0.05f, 0.05f);
        particles[i].ttl = RandomFloat(2.0f, 5.0f);

        particles[i].inactive = false;
    }
}

void ParticleSystem::Render(Image* framebuffer) {
    // Dibujar las partículas en el búfer de imagen
    for (int i = 0; i < MAX_PARTICLES; ++i) {
        if (!particles[i].inactive) {
            framebuffer->SetPixel(particles[i].position.x, particles[i].position.y,
                particles[i].color);
        }
    }
}

void ParticleSystem::Update(float dt, unsigned int width, unsigned int height) {
    // Actualizar la posición de las partículas
    for (int i = 0; i < MAX_PARTICLES; ++i) {
        if (!particles[i].inactive) {
            particles[i].position += particles[i].velocity * dt;

            // Aplicar la aceleración
            particles[i].velocity = Vector2(particles[i].velocity.x + particles[i].acceleration * dt, particles[i].velocity.y + particles[i].acceleration * dt);

            // Si la partícula sale de la pantalla, la desactivamos
            if (particles[i].position.x < 0.0f || particles[i].position.x >= width || particles[i].position.y < 0.0f || particles[i].position.y >= height) {
                particles[i].inactive = true;
            }
        }
    }
}
*/