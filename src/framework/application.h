#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"
#include "button.h"
#include "particlesystem.h"
#include "light.h"  
#include "material.h"  
#include "entity.h"
#include "shader.h"
#include "camera.h"
#include "texture.h"
#include "light.h"


class Application
{
public:

	// Window

	SDL_Window* window = nullptr;
	int window_width;
	int window_height;

	float time;

	//Tecles per interaccionar amb el programa
	float lletra;
	float let_c;

	//Uniform Data
	sUniformData sUD1;
	sUniformData sUD2;

	//Entity + Malla
	Entity myEntity2 = Entity();
	Entity myEntity1 = Entity();
	Mesh myMesh = Mesh();

	//Shader
	Shader* myShader2 = nullptr;
	Shader* myShader3 = nullptr;

	//Camera + Texture
	Camera myCamera = Camera();
	Texture* face_texture = new Texture();

	//Vector3 + Matrix44
	Vector3 eye = (0, 1, 1);
	Vector3 center = (0, 0, 0);
	Vector3 deu = (10, 10, 10);
	Matrix44 modelMatrix;

	//Material
	Material myMaterial1 = Material();
	Material myMaterial2 = Material();

	//Light
	Light* myLight = new Light((1, 1, 1), (4, 4, 4), (2, 2, 2));

	//Color Components
	ColorComponents myColorComponents;

	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame
	FloatImage* zBuffer;
	void OnKeyPressed(SDL_KeyboardEvent event);
	void OnMouseButtonDown(SDL_MouseButtonEvent event);
	void OnMouseButtonUp(SDL_MouseButtonEvent event);
	void OnMouseMove(SDL_MouseButtonEvent event);
	void OnWheel(SDL_MouseWheelEvent event);
	void OnFileChanged(const char* filename);

	// CPU Global framebuffer
	Image framebuffer;

	// Constructor and main methods
	Application(const char* caption, int width, int height);
	~Application();

	void Init(void);
	void Render(void);
	void Update(float dt);
	void Application::Option();


	// Other methods to control the app
	void SetWindowSize(int width, int height) {
		glViewport(0, 0, width, height);
		this->window_width = width;
		this->window_height = height;
	}

	Vector2 GetWindowSize()
	{
		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		return Vector2(float(w), float(h));
	}

};


