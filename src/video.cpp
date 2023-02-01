#include "video.h"

video::~video(){

	if(Window)
		SDL_DestroyWindow(Window);

	if(Renderer)
		SDL_DestroyRenderer(Renderer);

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool video::init(){
	return (SDL_InitSubSystem(SDL_INIT_VIDEO) == 0);
}

bool video::create_Window(const char* name, int width, int height){
	
	Window = SDL_CreateWindow(name, 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, 
		0
		);

	if(!Window)
		return false;

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

	return Renderer;
}

bool video::swap_Buffer(){
	SDL_RenderPresent(Renderer);
	return true;
}

bool video::clear_Buffer(int r, int g, int b, int a){
	SDL_SetRenderDrawColor(Renderer, r, g, b, a);
	return (SDL_RenderClear(Renderer) == 0);
}

bool video::draw_Line(int x1, int y1, int x2, int y2){
	SDL_SetRenderDrawColor(Renderer, 128, 128, 128, 255);
	return (SDL_RenderDrawLine(Renderer, x1, y1, x2, y2) == 0);
}