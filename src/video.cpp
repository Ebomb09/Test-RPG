#include "video.h"
#include <iostream>

video::~video(){

	if(Window)
		SDL_DestroyWindow(Window);

	if(Renderer)
		SDL_DestroyRenderer(Renderer);

	TTF_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool video::init(){
	return (SDL_InitSubSystem(SDL_INIT_VIDEO) == 0 && TTF_Init());
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

SDL_Texture* video::load_Texture(std::string filename){

	SDL_Texture* tex = textures.find(filename);

	if(!tex){
		SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
		tex = SDL_CreateTextureFromSurface(Renderer, surface);
		SDL_FreeSurface(surface);

		if(tex){
			SDL_Texture* old = textures.replace(tex, filename);
			SDL_DestroyTexture(old);
		}
	}

	return tex;
}

TTF_Font* video::load_Font(std::string filename, int ptsize){

	TTF_Font* font = fonts.find(filename);

	if(!font){
		font = TTF_OpenFont(filename.c_str(), ptsize);

		if(font){
			TTF_Font* old = fonts.replace(font, filename);
			TTF_CloseFont(old);
		}
	}

	return font;
}

bool video::draw_Line(int x1, int y1, int x2, int y2){
	SDL_SetRenderDrawColor(Renderer, 128, 128, 128, 255);
	return (SDL_RenderDrawLine(Renderer, x1, y1, x2, y2) == 0);
}

bool video::draw_Text(std::string text, int x, int y, std::string font){

	//return SDL_RenderCopy(Renderer, )
	return true;
}

bool video::draw_Texture(int x, int y, std::string image){

	SDL_Texture* tex = load_Texture(image);

	SDL_Rect src = {0, 0, 128, 128};
	SDL_Rect dst = {x, y, 128, 128};
	SDL_RenderCopy(Renderer, tex, &src, &dst);

	return true;
}