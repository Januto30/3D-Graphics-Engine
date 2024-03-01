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


int a1 = 1;

float a, b, c, d, e, f, lletra, u_aspectRatio, aug;



Shader* myShader = nullptr;

Camera myCamera = Camera();
Entity myEntity = Entity();
Mesh quad = Mesh();
Mesh myMesh = Mesh();
Matrix44 modelMatrix;

//-----------------
Shader* s = new Shader();
Texture* t = new Texture();
Texture* face_texture = new Texture();
//-----------------

//-----------------
Vector3 eye = (0, 1, 1);
Vector3 center = (0, 0, 0);
//-----------------

//-----LAB5 3D-----
Material myMaterial = Material();
sUniformData sUD;
Light myLight;
ColorComponents myColorComponents;
//-----------------

//-----------------

//-----------------

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
	myCamera.LookAt(eye, center, Vector3::UP);
	myCamera.SetPerspective(45 * DEG2RAD, float(window_width) / window_height, 0.01, 100);

	u_aspectRatio = framebuffer.width / framebuffer.height;


	a = false;
	lletra = 3.0f;
	aug = 0.f;
	s = new Shader();
	s = Shader::Get("shaders/quad.vs", "shaders/quad.fs");
	quad.CreateQuad();


	//Exercici filtres:
	t = Texture::Get("images/fruits.png");

	//Exercici mesh
	myEntity = Entity(modelMatrix, myMesh, &myMaterial);

	myMesh = Mesh();
	myMesh.LoadOBJ("meshes/lee.obj");

	myShader = Shader::Get("shaders/raster.vs", "shaders/raster.fs");
	face_texture = Texture::Get("textures/lee_color_specular.tga");

	myEntity.setMaterialTexture(face_texture);
	myEntity.setMesh(myMesh);
	sUD.projectioViewMatrix = myCamera.viewprojection_matrix;
	sUD.modelMatrixx = myEntity.getModelMatrix();
	sUD.tt = face_texture;
	sUD.cc = &myCamera;
	myMaterial.setShader(myShader);

	// Lab5 
	//sUD.cc = myCamera;
	//sUD.mm.setLight(myLight);
	

}

void Application::Render(void)
{
	if (lletra != 4.0) {
		s->Enable();
		s->SetFloat("u_aspectRatio", framebuffer.width / framebuffer.height);
		s->SetTexture("u_texture", t);
		s->SetFloat("aug_value", aug);
		quad.Render();
		Option();
		s->Disable();
	}
	if (lletra == 4.0) {
		myEntity.Render(sUD);
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
	case SDLK_1:printf("1"); lletra = 1.0f; break;
	case SDLK_2:printf("2"); lletra = 2.0f; break;
	case SDLK_3:printf("3"); lletra = 3.0f; break;
	case SDLK_4:printf("4"); lletra = 4.0f; break;


	case SDLK_a:printf("a"); a = true; b = c = d = e = f = false; break;
	case SDLK_b:printf("b"); b = true; a = c = d = e = f = false; break;
	case SDLK_c:printf("c"); c = true; b = a = d = e = f = false; break;
	case SDLK_d:printf("d"); d = true; b = c = a = e = f = false; break;
	case SDLK_e:printf("e"); e = true; b = c = d = a = f = false; break;
	case SDLK_f:printf("f"); f = true; b = c = d = e = a = false; break;

	case SDLK_p:printf("p"); aug += 100.0f; break;
	case SDLK_o:printf("o"); aug -= 100.0f; break;

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
		
		sUD.cc->Orbit(-mouse_delta.x * 0.1, Vector3::UP);
		sUD.cc->Orbit(-mouse_delta.y * 0.1, Vector3::RIGHT);
	}
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;
	sUD.cc->Zoom(dy < 0 ? 1.1 : 0.9);
}


void Application::OnFileChanged(const char* filename)
{
	Shader::ReloadSingleShader(filename);

}

void Application::Option() {
	if (lletra == 1) {
		s->SetFloat("lletra_value", 1.0f);
	}
	else if (lletra == 2) {
		s->SetFloat("lletra_value", 2.0f);
	}
	else if (lletra == 3) {
		s->SetFloat("lletra_value", 3.0f);
	}

	if (a == true) {
		s->SetFloat("b_value", 0.0f);
		s->SetFloat("c_value", 0.0f);
		s->SetFloat("d_value", 0.0f);
		s->SetFloat("e_value", 0.0f);
		s->SetFloat("f_value", 0.0f);

		s->SetFloat("u_value", 1.0f);
	}
	else if (b == true) {
		s->SetFloat("u_value", 0.0f);
		s->SetFloat("c_value", 0.0f);
		s->SetFloat("d_value", 0.0f);
		s->SetFloat("e_value", 0.0f);
		s->SetFloat("f_value", 0.0f);

		s->SetFloat("b_value", 1.0f);
	}
	else if (c == true) {
		s->SetFloat("b_value", 0.0f);
		s->SetFloat("u_value", 0.0f);
		s->SetFloat("d_value", 0.0f);
		s->SetFloat("e_value", 0.0f);
		s->SetFloat("f_value", 0.0f);

		s->SetFloat("c_value", 1.0f);
	}
	else if (d == true) {
		s->SetFloat("b_value", 0.0f);
		s->SetFloat("c_value", 0.0f);
		s->SetFloat("u_value", 0.0f);
		s->SetFloat("e_value", 0.0f);
		s->SetFloat("f_value", 0.0f);

		s->SetFloat("d_value", 1.0f);
	}
	else if (e == true) {
		s->SetFloat("b_value", 0.0f);
		s->SetFloat("c_value", 0.0f);
		s->SetFloat("d_value", 0.0f);
		s->SetFloat("u_value", 0.0f);
		s->SetFloat("f_value", 0.0f);

		s->SetFloat("e_value", 1.0f);
	}
	else if (f == true) {
		s->SetFloat("b_value", 0.0f);
		s->SetFloat("c_value", 0.0f);
		s->SetFloat("d_value", 0.0f);
		s->SetFloat("e_value", 0.0f);
		s->SetFloat("u_value", 0.0f);

		s->SetFloat("f_value", 1.0f);
	}
}