#ifndef BASE_INTERFACE_H
#define BASE_INTERFACE_H

struct interface;
class game;

typedef void (*callbackFn)(interface*);

struct interface{
	callbackFn callback;

	interface();

	virtual void update(game* Game)=0;
	virtual void draw(game* Game)=0;
};

#endif