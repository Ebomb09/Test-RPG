#include "entity/base.h"

entity::entity(){
	what = type::Generic;
	solid = false;
}

bool entity::interact(game *Game, worldmap *World){
	return false;
}

void entity::update(game *Game, worldmap *World){
	return;
}

void entity::draw(game *Game, worldmap *World){
	return;
}

entity::type entity::get_Type(){
	return what;
}