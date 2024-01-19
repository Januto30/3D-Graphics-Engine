#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 

Image blue, black, circle, cyan, clear, eraser, green, line, load, pink, rectangle, red, save;
Button blue, black, circle, cyan, clear, eraser, green, line, load, pink, rectangle, red, save;

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

	if (blue.LoadPNG("images/blue.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (black.LoadPNG("images/black.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (circle.LoadPNG("images/circle.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (cyan.LoadPNG("images/cyan.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (clear.LoadPNG("images/clear.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (eraser.LoadPNG("images/eraser.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (green.LoadPNG("images/green.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (line.LoadPNG("images/line.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (load.LoadPNG("images/load.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (pink.LoadPNG("images/pink.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (rectangle.LoadPNG("images/rectangle.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (red.LoadPNG("images/red.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}

	if (save.LoadPNG("images/save.png", true)) {

		std::cout << "Imagen cargada exitosamente." << std::endl;
	}
	else {
		std::cerr << "No se pudo cargar la imagen." << std::endl;
	}
}

// Render one frame
void Application::Render(void)
{
	framebuffer.Fill(Color::WHITE);
	framebuffer.DrawImage(load, 30, 20, true);
	framebuffer.DrawImage(save, 81, 20, true);
	framebuffer.DrawImage(eraser, 132, 20, true);
	framebuffer.DrawImage(line, 183, 20, true);
	framebuffer.DrawImage(rectangle, 234, 20, true);
	framebuffer.DrawImage(circle, 285, 20, true);
	framebuffer.DrawImage(black, 336, 20, true);
	framebuffer.DrawImage(red, 387, 20, true);
	framebuffer.DrawImage(green, 438, 20, true);
	framebuffer.DrawImage(blue, 489, 20, true);
	framebuffer.DrawImage(cyan, 540, 20, true);
	framebuffer.DrawImage(pink, 591, 20, true);
	framebuffer.Render();
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
		case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
		case SDLK_1: framebuffer.DrawLineDDA(100,100,400,300,Color::CYAN); break; // ESC key, kill the app

	}
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {

	}
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {

	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	
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