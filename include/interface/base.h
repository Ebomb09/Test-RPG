#ifndef BASE_INTERFACE_H
#define BASE_INTERFACE_H

struct interface;
class game;

typedef void (*callbackFn)(interface*);

struct interface{
	game* Game;
	callbackFn callback;

	interface();

	virtual void update()=0;
	virtual void draw()=0;
};

#endif