#include "video.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include <iostream>

video::~video(){

	for(int i = 0; i < textures.count(); i ++)
		SDL_DestroyTexture(textures[i]);
	
	for(int i = 0; i < fonts.count(); i ++)
		TTF_CloseFont(fonts[i]);

	if(Window)
		SDL_DestroyWindow(Window);

	if(Renderer)
		SDL_DestroyRenderer(Renderer);

	IMG_Quit();
	TTF_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool video::init(){
	return (SDL_InitSubSystem(SDL_INIT_VIDEO) == 0 && TTF_Init() && IMG_Init(IMG_INIT_PNG));
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
		tex = IMG_LoadTexture(Renderer, filename.c_str());

		if(tex){
			SDL_Texture* old = textures.replace(tex, filename);
			SDL_DestroyTexture(old);
		}
	}

	return tex;
}

TTF_Font* video::load_Font(std::string filename, int ptsize){

	std::string id_name = filename + ":" + std::to_string(ptsize);

	TTF_Font* font = fonts.find(id_name);

	if(!font){
		font = TTF_OpenFont(filename.c_str(), ptsize);

		if(font){
			TTF_Font* old = fonts.replace(font, id_name);
			TTF_CloseFont(old);
		}
	}

	return font;
}

bool video::draw_Line(int x1, int y1, int x2, int y2){
	SDL_SetRenderDrawColor(Renderer, 128, 128, 128, 255);
	return (SDL_RenderDrawLine(Renderer, x1, y1, x2, y2) == 0);
}

bool video::draw_Text(int x, int y, std::string text, std::string fontname, int ptsize){

	std::string id_name = text + ":" + fontname + ":" + std::to_string(ptsize);

	TTF_Font* font = load_Font(fontname, ptsize);
	SDL_Texture* tex = load_Texture(id_name);

	if(!tex){
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {0, 0, 0, 255});
		tex = SDL_CreateTextureFromSurface(Renderer, surface);
		SDL_FreeSurface(surface);

		if(tex){
			SDL_Texture* old = textures.replace(tex, id_name);
			SDL_DestroyTexture(old);
		}
	}

	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);

	SDL_Rect src = {0, 0, w, h};
	SDL_Rect dst = {x, y, w, h};

	return (SDL_RenderCopy(Renderer, tex, &src, &dst) == 0);
}

bool video::draw_TextClip(int x, int y, int clip_w, int clip_h, std::string text, std::string fontname, int ptsize){

	TTF_Font* font = load_Font(fontname, ptsize);

	int count, start;
	int h = 0;
	while(text != "" && h < clip_h){
		TTF_MeasureText(font, text.c_str(), clip_w, NULL, &count);

		// Default next start is after text that can fit
		start = count;

		// If it doesn't fit all content then 
		// find next space / dash for delimiter
		if(count < text.size()){

			for(int i = count-1; i >= 0; i --){

				if (text[i] == ' ' || text[i] == '-'){
					count = i;
					start = i + 1;
					break;
				}
			}
		}

		if(!draw_Text(x, y+h, text.substr(0, count), fontname, ptsize))
			return false;

		// Substring until end and continue rendering
		text = text.substr(start);
		h += ptsize;
	}

	return true;
}

bool video::draw_Texture(int x, int y, std::string image){

	SDL_Texture* tex = load_Texture(image);

	SDL_Rect src = {0, 0, 128, 128};
	SDL_Rect dst = {x, y, 128, 128};

	return (SDL_RenderCopy(Renderer, tex, &src, &dst) == 0);
}

bool video::draw_TextureClip(int x, int y, int clip_x, int clip_y, int clip_w, int clip_h, double scale_w, double scale_h, std::string image){

	SDL_Texture* tex = load_Texture(image);

	SDL_Rect src = {
		clip_x * clip_w, 
		clip_y * clip_h, 
		clip_w, 
		clip_h
	};
	SDL_Rect dst = {
		x, 
		y, 
		(int)(clip_w * scale_w), 
		(int)(clip_h * scale_h)
	};

	return (SDL_RenderCopy(Renderer, tex, &src, &dst) == 0);
}

bool video::draw_Colour(int r, int g, int b, int a){
	return (SDL_SetRenderDrawColor(Renderer, r, g, b, a) == 0);	
}

bool video::draw_Rectangle(int x, int y, int w, int h){
	SDL_Rect rect = {x, y, w, h};
	return (SDL_RenderDrawRect(Renderer, &rect) == 0);
}

bool video::draw_FillRectangle(int x, int y, int w, int h){
	SDL_Rect rect = {x, y, w, h};
	return (SDL_RenderFillRect(Renderer, &rect) == 0);
}