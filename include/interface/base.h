#ifndef BASE_INTERFACE_H
#define BASE_INTERFACE_H

struct interface;
class game;

struct interface{
	virtual void update(game* Game)=0;
	virtual void draw(game* Game)=0;
};

#endif