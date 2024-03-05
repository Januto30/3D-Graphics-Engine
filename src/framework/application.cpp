#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "button.h"
#include "framework.h"
#include "particlesystem.h"
#include "entity.h"
#include "camera.h"
#include "light.h"
#include "material.h"


Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

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
	sUD2.let_c = 0;
	//Assignem valors a Material
	myMaterial1.setKa(deu);
	myMaterial1.setKd(deu);
	myMaterial1.setKs(deu);

	myMaterial2.setKa(deu);
	myMaterial2.setKd(deu);
	myMaterial2.setKs(deu);


	//Assignem valors a Uniform Data
	sUD1.Ka = myMaterial1.getKa();
	sUD1.Kd = myMaterial1.getKd();
	sUD1.Ks = myMaterial1.getKs();

	sUD2.Ka = myMaterial2.getKa();
	sUD2.Kd = myMaterial2.getKd();
	sUD2.Ks = myMaterial2.getKs();


	//Assignem posició i perspectiva a la càmera
	myCamera.LookAt(eye, center, Vector3::UP);
	myCamera.SetPerspective(45 * DEG2RAD, float(window_width) / window_height, 0.01, 100);


	//Exercici mesh
	myEntity1 = Entity(modelMatrix, myMesh, &myMaterial1);
	myEntity2 = Entity(modelMatrix, myMesh, &myMaterial2);


	//Carguem malla, shaders i textures
	myMesh.LoadOBJ("meshes/lee.obj");

	myShader2 = Shader::Get("shaders/gouraud.vs", "shaders/gouraud.fs");
	myShader3 = Shader::Get("shaders/phong.vs", "shaders/phong.fs");
	
	//face_texture = Texture::Get("textures/lee_normal.tga");
	face_texture = Texture::Get("textures/lee_color_specular.tga");


	//Assignem textura al material de les nostres entitats
	myEntity1.setMaterialTexture(face_texture);
	myEntity2.setMaterialTexture(face_texture);


	//Assignem malla a les nostres entitats
	myEntity1.setMesh(myMesh);
	myEntity2.setMesh(myMesh);


	//Assignem més valors a les Uniform Data
	sUD1.projectioViewMatrix = myCamera.viewprojection_matrix;
	sUD2.projectioViewMatrix = myCamera.viewprojection_matrix;

	sUD1.modelMatrixx = myEntity1.getModelMatrix();
	sUD2.modelMatrixx = myEntity2.getModelMatrix();

	sUD1.tt = face_texture;
	sUD2.tt = face_texture;

	sUD1.cc = &myCamera;
	sUD2.cc = &myCamera;

	sUD1.ll_pos = myLight->getPos();
	sUD2.ll_pos = myLight->getPos();

	sUD1.color = { (1, 1, 1) };
	sUD2.color = { (1, 1, 1) };


	//Assignem shaers als nostres materials
	myMaterial1.setShader(myShader2);
	myMaterial2.setShader(myShader3);




}

void Application::Render(void)
{
	if (lletra != 4.0) {
		myEntity1.Render(sUD1);
	}
	if (lletra == 4.0) {

		myEntity2.Render(sUD2);
	}

}

void Application::Update(float seconds_elapsed)
{

}

void Application::OnKeyPressed(SDL_KeyboardEvent event)
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch (event.keysym.sym) {
	case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
	case SDLK_g: lletra = 1.0f; break;
	case SDLK_p: lletra = 4.0f; break;
	case SDLK_c: if (sUD2.let_c == 0) { sUD2.let_c = 1; }
			   else { sUD2.let_c = 0; } break;


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


void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {
		
		sUD1.cc->Orbit(-mouse_delta.x * 0.1, Vector3::UP);
		sUD1.cc->Orbit(-mouse_delta.y * 0.1, Vector3::RIGHT);
		sUD2.cc->Orbit(-mouse_delta.x * 0.1, Vector3::UP);
		sUD2.cc->Orbit(-mouse_delta.y * 0.1, Vector3::RIGHT);
	}
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;
	sUD1.cc->Zoom(dy < 0 ? 1.1 : 0.9);
	sUD2.cc->Zoom(dy < 0 ? 1.1 : 0.9);

}


void Application::OnFileChanged(const char* filename)
{
	Shader::ReloadSingleShader(filename);

}
