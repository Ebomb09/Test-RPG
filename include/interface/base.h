#ifndef BASE_INTERFACE_H
#define BASE_INTERFACE_H

class game;

struct interface{
	game* Game;
	virtual void update()=0;
	virtual void draw()=0;
};

#endif