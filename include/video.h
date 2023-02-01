#ifndef VIDEO_H
#define VIDEO_H

#include <SDL2/SDL.h>

class video{

protected:
	SDL_Window* Window;
	SDL_Renderer* Renderer;

	bool init();
	bool create_Window(const char* name, int width, int height);
	bool swap_Buffer();
	bool clear_Buffer(int r, int g, int b, int a);

public:
	~video();

	bool draw_Line(int x1, int y1, int x2, int y2);
};

#endif