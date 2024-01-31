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

bool ind = false;
bool mult = false;
float r = 1.0f;
float t = 1.0f;
float f = 1.0f;
float b = -1.0f;
float n = -1.0f;
float l = -1.0f;

Camera camera = Camera();

Entity myEntity = Entity();
Entity myEntity2 = Entity();
Entity myEntity3 = Entity();
Entity myEntity4 = Entity();

Mesh myMesh = Mesh();
Mesh myMesh2 = Mesh();
Mesh myMesh3 = Mesh();
Mesh myMesh4 = Mesh();

Matrix44 modelMatrix;
Matrix44 modelMatrix2;
Matrix44 modelMatrix3;
Matrix44 modelMatrix4;

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
	myMesh4.LoadOBJ("meshes/lee.obj");

	myEntity.setMesh(myMesh);
	myEntity2.setMesh(myMesh2);
	myEntity3.setMesh(myMesh3);
	myEntity4.setMesh(myMesh4);

	myEntity3.setRotate(true);
	myEntity2.setEscalate(true);
	myEntity.setTranslate(true);
	Vector3 rotation_axis(0.0f, 1.0f, 0.0f);
	modelMatrix4.RotateLocal(1 * (PI / 10.0f), rotation_axis);

	modelMatrix.SetIdentity();
	modelMatrix2.SetIdentity();
	modelMatrix3.SetIdentity();
 
	modelMatrix.Translate(-0.65, 0, 0);
	modelMatrix3.Translate(-0.1,-0.8,-1.0);
	modelMatrix2.Translate(+0.7, -0.2, 0);
	modelMatrix4.Translate(0, -0.5, 0);

	modelMatrix._11 = 1.2;
	modelMatrix._22 = 1.2;
	modelMatrix._33 = 1.2;

	modelMatrix3._11 = 2.2;
	modelMatrix3._22 = 2.2;
	modelMatrix3._33 = 2.2;

	modelMatrix4._11 = 2;
	modelMatrix4._22 = 2;
	modelMatrix4._33 = 2;

	myEntity.setModelMatrix(modelMatrix);
	myEntity2.setModelMatrix(modelMatrix2);
	myEntity3.setModelMatrix(modelMatrix3);
	myEntity4.setModelMatrix(modelMatrix4);

	camera.SetOrthographic(camera.left, camera.right, camera.top, camera.bottom, camera.near_plane, camera.far_plane);
}

void Application::Render(void)
{
	camera.SetOrthographic(l, r, t, b, n, f);
	if (ind == true) {
		myEntity4.Render(&framebuffer, &camera, Color::CYAN);
	}
	if (mult == true){
		myEntity.Render(&framebuffer, &camera, Color::BLUE);
		myEntity2.Render(&framebuffer, &camera, Color::GREEN);
		myEntity3.Render(&framebuffer, &camera, Color::RED);
	}
	framebuffer.Render();
}

void Application::Update(float seconds_elapsed)
{
	framebuffer.Fill(Color::BLACK);
	//myEntity.Update(0.5f);
	myEntity2.Update(0.05f);
	myEntity3.Update(0.1f);
}

void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch(event.keysym.sym) {
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the appç
		case SDLK_1:printf("1"); mult = false;  ind = true; framebuffer.Fill(Color::BLACK); break;
		case SDLK_2:printf("2"); ind = false; mult = true;	framebuffer.Fill(Color::BLACK); break;
		case SDLK_o:printf("o"); camera.SetOrthographic(l, r, t, b, n, f); break;
		case SDLK_p:printf("p"); camera.SetPerspective(camera.fov, camera.aspect, camera.near_plane, camera.far_plane);break;
		case SDLK_n:printf("n"); /*falta esciure codi*/		break;
		case SDLK_f:printf("f"); /*falta esciure codi*/		break;
		case SDLK_MINUS:printf("-"); /*falta esciure codi*/ break;
		case SDLK_PLUS:	printf("+"); /*falta esciure codi*/ break;
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

}


void Application::OnFileChanged(const char* filename)
{
	Shader::ReloadSingleShader(filename);
	
}