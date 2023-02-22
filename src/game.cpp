#include <chrono>
#include <thread>
#include <iostream>
#include "game.h"

game::game(){
	game_loop = true;
	frames_per_second = 60;
	delta_time = 0;
	init();

	load_Moves();
	load_Enemies();
}

game::~game(){
	
}

void game::init(){

	for(int i = 0; i < game::characters::maxpartysize; i ++)
		Party[i] = NULL;

	MessageBox.openFile("data/dialogue");

	video::init();
	video::create_Window("RPG Test", 640, 480);

	input::init();

	audio::init();
}

void game::load_Return(){
	active_interfaces.pop_front();
}

void game::load_MainMenu(){
	active_interfaces.clear();
	active_interfaces.push_front(&MainMenu);
}

void game::load_MessageBox(std::string section){
	MessageBox.gotoSection(section.c_str());

	active_interfaces.push_front(&MessageBox);
	run(&MessageBox);
}

bool game::load_Battle(point position){
	Battle.set(this, position);

	active_interfaces.push_front(&Battle);
	run(&Battle);

	return Battle.get();
}

std::string game::load_InputBox(std::string prompt, std::string default_string, int limit){
	InputBox.set(this, prompt, default_string, limit);

	active_interfaces.push_front(&InputBox);
	run(&InputBox);

	return get_string();
}

int game::load_PartyPosition(character* ch){
	PartyPosition.set(ch);

	active_interfaces.push_front(&PartyPosition);
	run(&PartyPosition);

	return PartyPosition.get();
}

void game::load_WorldMap(std::string map){
	WorldMap.load_Map(map);

	active_interfaces.clear();
	active_interfaces.push_front(&WorldMap);
}

void game::run(interface* watch){

	using clock = std::chrono::high_resolution_clock;
	using time_t = clock::time_point;
	using duration_t = std::chrono::duration<double>;

	while(game_loop){

		// Get start time
		time_t time_start = clock::now();
		double time_per_frame = 1. / (double)frames_per_second;

		// Check if there are any inputs
		input::poll();

		if(quit)
			stop();

		// Only update logic for the top most interface
		if(!active_interfaces.empty())
			active_interfaces.front()->update(this);

		// If the game wants to run an interface until it's finished
		// ie. no longer active
		if(watch){

			if(active_interfaces.empty() || active_interfaces.front() != watch)
				return;
		}

		// Draw from bottom to top
		video::clear_Buffer(255, 255, 255, 255);

		for(std::list<interface*>::reverse_iterator it = active_interfaces.rbegin(); it != active_interfaces.rend(); it ++)
			(*it)->draw(this);

		video::swap_Buffer();

		// Calculate delta time and sleep if needed
		// to achieve the desired FPS
		duration_t duration = std::chrono::duration_cast<duration_t>(clock::now() - time_start);

		if(duration.count() < time_per_frame){
			while(clock::now() < time_start + duration_t(time_per_frame - duration.count()));

			delta_time = time_per_frame;
		}else
			delta_time = duration.count();
	}
}

void game::stop(){
	game_loop = false;
}

double game::delta_Time(){
	return delta_time;
}

bool game::is_PartyMember(character* ch){

	for(int i = 0; i < characters::maxpartysize; i ++){
		if(Party[i] == ch)
			return true;
	}

	return false;
}

bool game::is_Enemy(character* ch){

	for(int i = 0; i < enemies::total; i ++){
		if(&Enemies[i] == ch)
			return true;
	}

	return false;
}

void game::load_Party(std::string fname){

	Characters[characters::wizardcat] = {
		"data/textures/WizardCat.png", 
		"WizardCat",
		{100},
		{100},
		{&Moves[moves::attack], &Moves[moves::item], &Moves[moves::fire]}
	};
}

void game::load_Enemies(){
	
	Enemies[enemies::slime] = {
		"data/textures/slime.png",
		"Slime",
		{100},
		{100},
		{&Moves[moves::fire]}
	};
}

void game::load_Moves(){

	Moves[moves::attack] = {
		"data/textures/attack.fx",
		"Attack"
	};

	Moves[moves::item] = {
		"data/textures/item.fx",
		"Item"
	};

	Moves[moves::ice] = {
		"data/textures/ice.fx",
		"Ice"
	};

	Moves[moves::fire] = {
		"data/textures/fire.fx",
		"Fire"
	};

	Moves[moves::thunder] = {
		"data/textures/ice.fx",
		"Thunder"
	};
}

