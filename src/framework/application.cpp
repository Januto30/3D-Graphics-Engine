#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "button.h"
#include "framework.h"
#include "particlesystem.h"
#include "framework/entity.h"
#include "image.h"
#include "camera.h"

Image myImage;
Camera mainCamera;

Camera camera = Camera();
Entity myEntity = Entity();
Entity myEntity2 = Entity();
Entity myEntity3 = Entity();

Mesh myMesh = Mesh();
Mesh myMesh2 = Mesh();
Mesh myMesh3 = Mesh();


FloatImage* zBuffer = new FloatImage(300, 300);
Matrix44 modelMatrix;
Matrix44 modelMatrix2;
Matrix44 modelMatrix3;

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

	myMesh.LoadOBJ("meshes/cleo.obj");
	myMesh2.LoadOBJ("meshes/anna.obj");
	myMesh3.LoadOBJ("meshes/lee.obj");

	myEntity.setMesh(myMesh);
	myEntity2.setMesh(myMesh2);
	myEntity3.setMesh(myMesh3);

	modelMatrix.SetIdentity();
	modelMatrix2.SetIdentity();
	modelMatrix3.SetIdentity();

	modelMatrix.Translate(-0.65, 0, 0);
	modelMatrix3.Translate(-0.10,-0.8,0);
	modelMatrix2.Translate(+0.5, -0.1, 0);

	modelMatrix._11 = 1.2;
	modelMatrix._22 = 1.2;
	modelMatrix._33 = 1.2;

	modelMatrix2._11 = 1.7;
	modelMatrix2._22 = 1.7;
	modelMatrix2._33 = 1.7;

	modelMatrix3._11 = 2.2;
	modelMatrix3._22 = 2.2;
	modelMatrix3._33 = 2.2;


	Vector3 rotation_axis(0.0f, 1.0f, 0.0f);

	modelMatrix3.RotateLocal(0*(PI / 8.0f), rotation_axis);




	myEntity.setModelMatrix(modelMatrix);
	myEntity2.setModelMatrix(modelMatrix2);
	myEntity3.setModelMatrix(modelMatrix3);

	camera.SetOrthographic(-1,1,1,-1,-1,1);

}

// Render one frame
void Application::Render(void)
{
	
	myEntity.Render(&framebuffer, &camera, Color::BLUE);
	myEntity2.Render(&framebuffer, &camera, Color::GREEN);
	myEntity3.Render(&framebuffer, &camera, Color::RED);

	framebuffer.Render();
}

// Called after render
void Application::Update(float seconds_elapsed)
{
	myEntity.Update(0.5f);
}

//keyboard press event 
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the appç
		case SDLK_1:printf("1");		break;
		case SDLK_2:printf("2");		break;
		case SDLK_o:printf("o");		break;
		case SDLK_p:printf("p");		break;
		case SDLK_n:printf("n");		break;
		case SDLK_f:printf("f");		break;
		case SDLK_MINUS:printf("-");	break;
		case SDLK_PLUS:	printf("+");	break;
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