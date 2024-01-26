#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "button.h"
#include "framework.h"

Button blue("images/blue.png", { 489,20 });
Button black("images/black.png", { 336,20 });
Button circle("images/circle.png", { 285,20 });
Button cyan("images/cyan.png", { 540,20 });
Button clear("images/clear.png", { 89,20 });
Button eraser("images/eraser.png", { 132,20 });
Button green("images/green.png", { 438,20 });
Button load("images/load.png", { 30,20 });
Button pink("images/pink.png", { 591,20 });
Button rectangle("images/rectangle.png", { 234,20 });
Button red("images/red.png", { 387,20 });
Button save("images/save.png", { 81,20 });
Button line("images/line.png", { 183,20 });
Button triangle("images/triangle.png", { 693,20 });
Button filled("images/fill.png", { 642,20 });
Image toolbar;
Color c = Color::GREEN;
Vector2 line_start, line_end, rec_1, rec_2, rec_4, rec_3, punt, punt2, t1, t2, t3;
int anchura = 1, int tecla = -1, int d = 13;
bool Eraseing = false, circleb = false, filleds = false, triangles = false, isDrawingRec = false, isDrawingLine = false;
Image myImage;



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
	toolbar.LoadPNG("images/toolbar.png");
}

// Render one frame
void Application::Render(void)
{
	framebuffer.DrawImage(toolbar, 0, 0, true);
	framebuffer.DrawImage(triangle.getImage(), 693, 20, true);
	framebuffer.DrawImage(filled.getImage(), 642, 20, true);
	framebuffer.DrawImage(load.getImage(), 30, 20, true);
	framebuffer.DrawImage(save.getImage(), 81, 20, true);
	framebuffer.DrawImage(eraser.getImage(), 132, 20, true);
	framebuffer.DrawImage(line.getImage(), 183, 20, true);
	framebuffer.DrawImage(rectangle.getImage(), 234, 20, true);
	framebuffer.DrawImage(circle.getImage(), 285, 20, true);
	framebuffer.DrawImage(black.getImage(), 336, 20, true);
	framebuffer.DrawImage(red.getImage(), 387, 20, true);
	framebuffer.DrawImage(green.getImage(), 438, 20, true);
	framebuffer.DrawImage(blue.getImage(), 489, 20, true);
	framebuffer.DrawImage(cyan.getImage(), 540, 20, true);
	framebuffer.DrawImage(pink.getImage(), 591, 20, true);


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
		case SDLK_1: framebuffer.DrawLineDDA(line_start.x, line_start.y, line_end.x, line_end.y, c); break;
		case SDLK_2: framebuffer.DrawRect(rec_1.x, rec_1.y, rec_2.x, rec_2.y, c, anchura, fill, c); 
			printf("maquina_inicial: (%f, %f), maquina_final: (%f, %f)\n", rec_1.x, rec_1.y, rec_2.x, rec_2.y);
			break;
		case SDLK_3: framebuffer.DrawCircle(punt.x, punt.y, d, c, anchura, fill, c); break;
		case SDLK_4: framebuffer.DrawTriangle(t1,t2,t3,c,fill,c);
		case SDLK_5: //Paint; break;
		case SDLK_6: //Animation; break;
		case SDLK_f: if (fill == false) fill = true; else fill = false; break;
		case SDLK_PLUS:
			anchura += 10;
			if (anchura <= 0) {
				anchura = 1;
			}
			printf("%d ", anchura);
			break;
		case SDLK_MINUS:
			anchura -= 10;
			if (anchura <= 0) {
				anchura = 1; // Ensure anchura is always greater than or equal to 1
			}
			printf("%d ", anchura);
			break;


	}
}

void Application::OnMouseButtonDown(SDL_MouseButtonEvent event) {

	if (event.button == SDL_BUTTON_LEFT) {
		Vector2 mousePosition(event.x, float(event.y) - float(framebuffer.height));

		if (line.IsMouseInside({ mouse_position.x, mouse_position.y })) {
		} else {
			line_start.x = event.x;
			line_start.y = float(framebuffer.height)-event.y-60;
			isDrawingLine = true;

		}
		if (black.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			c = Color::BLACK;
		}
		if (red.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			c = Color::RED;
		}
		if (green.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			c = Color::GREEN;
		}
		if (cyan.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			c = Color::CYAN;
		}
		if (pink.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			c = Color::PURPLE;
		}
		if (blue.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			c = Color::BLUE;
		}
		if (load.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.Fill(Color::BLACK);
		}
		if (save.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.SaveTGA("paint.tga");
		}

		if (rectangle.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			if (rec_1.y > rec_2.y) {
				framebuffer.DrawRect(rec_1.x, rec_2.y, rec_2.x, rec_1.y, c, anchura, fill, c);
			}
			else {
				framebuffer.DrawRect(rec_1.x, rec_2.y, rec_2.x, rec_1.y, c, anchura, fill, c);
			}
		}
		else {
			rec_1.x = event.x;
			rec_1.y = float(framebuffer.height) - event.y;
			isDrawingRec = true;

		}
		if (eraser.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.Eraser(line_start.x, line_start.y);
		}
		else {
			line_start.x = event.x;
			line_start.y = float(framebuffer.height) - event.y - 60;
			Eraseing = true;
		}
		if (circle.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.DrawCircle(punt.x, punt.y, d, c, anchura, fill, c);
		} else {
			punt.x = event.x;
			punt.y = float(framebuffer.height) - event.y-60;
			circleb = true;
		}
		if (circle.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.DrawCircle(punt.x, punt.y, d, c, anchura, fill, c);
		}
		else {
			punt.x = event.x;
			punt.y = float(framebuffer.height) - event.y - 60;
			circleb = true;
		}
		if (triangle.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.DrawTriangle(t1, t2, t3, c, fill, c);
		}
		else {
			t1.x = event.x;
			t1.y = float(framebuffer.height) - event.y - 60;
			t3.x = event.x + 50;
			t3.y = float(framebuffer.height) - event.y - 10;
			triangles = true;
		}
		if (filled.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.Fill(c);
			filleds = true;
		}

	}

}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		Vector2 mousePosition(event.x, float(event.y) - float(framebuffer.height));

		if (line.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.DrawLineDDA(line_start.x, line_start.y, line_end.x, line_end.y, c);

		}
		else {
			line_end.x = event.x;
			line_end.y = float(framebuffer.height) - event.y - 50;

			isDrawingLine = true;
		}
		if (rectangle.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			if (rec_1.y > rec_2.y) {
				framebuffer.DrawRect(rec_1.x, rec_2.y, rec_2.x, rec_1.y, c, anchura, fill, c);
			}
			else {
				framebuffer.DrawRect(rec_1.x, rec_2.y, rec_2.x, rec_1.y, c, anchura, fill, c);
			}
		}
		else {
			rec_2.x = event.x;
			rec_2.y = event.y;
			isDrawingRec = true;
			printf("usuer_inicial: (%f, %f), usuer_final: (%f, %f)\n", rec_1.x, rec_1.y, rec_2.x, rec_2.y);
		} 
		if (eraser.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.Eraser(line_end.x, line_end.y);
		}
		else {
			line_end.x = event.x;
			line_end.y = float(framebuffer.height) - event.y - 60;
			Eraseing = true;
		} 
		if (circle.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.DrawCircle(punt.x, punt.y, d, c, anchura, fill, c);
		}
		else {
			punt2.x = event.x;
			punt2.y = float(framebuffer.height) - event.y - 60;
			int x = abs(punt2.x - punt.x);
			int y = abs(punt2.y - punt.y);

			d = (x ^ 2 + y ^ 2) ^ (1/2);
			circleb = true;
		}
		if (triangle.IsMouseInside({ mouse_position.x, mouse_position.y })) {
			framebuffer.DrawTriangle(t1, t2, t3, c, fill, c);
		}
		else {
			t2.x = event.x;
			t2.y = float(framebuffer.height) - event.y - 60;
			triangles = true;
		}

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