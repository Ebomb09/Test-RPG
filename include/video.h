#ifndef VIDEO_H
#define VIDEO_H

#include <utility>
#include <string>

#include "SDL2/SDL.h"
#include "SDL_ttf.h"

#include "page.h"

class video{

protected:
	SDL_Window* Window;
	SDL_Renderer* Renderer;

	page<SDL_Texture*, std::string, 8> textures;
	page<TTF_Font*, std::string, 4> fonts;
	
	SDL_Texture* load_Texture(std::string filename);
	TTF_Font* load_Font(std::string filename, int ptsize);

	bool init();
	bool create_Window(const char* name, int width, int height);
	bool swap_Buffer();
	bool clear_Buffer(int r, int g, int b, int a);

public:
	~video();

	bool draw_Colour(int r, int g, int b, int a);
	bool draw_Line(int x1, int y1, int x2, int y2);
	bool draw_Text(int x, int y, std::string text, std::string fontname, int ptsize);
	bool draw_TextClip(int x, int y, int w, int h, std::string text, std::string fontname, int ptsize);
	bool draw_Texture(int x, int y, std::string image);
	bool draw_Rectangle(int x, int y, int w, int h);
};

#endif