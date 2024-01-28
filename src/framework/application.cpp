#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "button.h"
#include "framework.h"
#include "particlesystem.h"
#include "framework/entity.h"
#include "image.h"

Camera myCamera;
Entity myEntity;
Mesh myMesh;
Image myImage;
Camera mainCamera;
FloatImage* zBuffer = new FloatImage(300, 300);
Mesh p;


float modelMatrix[] = {
	1.0f, 0.0f, 0.0f, 2.0f,
	0.0f, 1.0f, 0.0f, 3.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};
Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->framebuffer.Resize(w, h);

}
Application::~Application()
{

}
void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
	myMesh.LoadOBJ("meshes/lee.obj");
	myEntity.setMesh(&myMesh);
	myEntity.setModelMatrix(modelMatrix);
	myCamera.fov = 45;
	myCamera.near_plane = 0.01;
	myCamera.far_plane = 100;
	
}

// Render one frame
void Application::Render(void)
{
	
	myCamera.UpdateViewMatrix();
	myCamera.UpdateViewProjectionMatrix();
	myEntity.Render(&framebuffer, &myCamera, Color::BLUE);
	

}

// Called after render
void Application::Update(float seconds_elapsed)
{
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the appç
	
	}
}

void Application::OnMouseButtonDown(SDL_MouseButtonEvent event) {

	if (event.button == SDL_BUTTON_LEFT) {

	}

}

void Application::OnMouseButtonUp(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {

	}
}


void Application::OnMouseMove(SDL_MouseButtonEvent event){

}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;

	// ...
}

void Application::OnFileChanged(const char* filename)
{
	Shader::ReloadSingleShader(filename);
	
}