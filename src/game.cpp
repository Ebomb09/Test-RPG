#include <chrono>
#include <thread>
#include <iostream>
#include "game.h"

game::game(){
	game_loop = true;
	frames_per_second = 60.;
	init();
}

game::~game(){
	
}

void game::init(){

	for(int i = 0; i < max_party_size; i ++)
		party[i] = NULL;

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
	using duration_t = std::chrono::duration<double, std::milli>;

	while(game_loop){

		// Get start time of the execution loop
		double seconds_per_frame = 1 / frames_per_second;
		time_t time_start = clock::now();

		// Check if there are any inputs
		input::poll();

		if(quit)
			stop();

		// Only update logic for the top most interface
		if(!active_interfaces.empty())
			active_interfaces.front()->update(this);

		// Draw from bottom to top
		video::clear_Buffer(255, 255, 255, 255);

		for(std::list<interface*>::reverse_iterator it = active_interfaces.rbegin(); it != active_interfaces.rend(); it ++)
			(*it)->draw(this);

		video::swap_Buffer();

		// Calculate delta time and sleep if needed
		// to achieve the desired FPS
		time_t time_end = clock::now();
		duration_t duration = std::chrono::duration_cast<duration_t>(time_end - time_start);

		if(duration.count() < seconds_per_frame * 1000.){
			double diff = seconds_per_frame * 1000. - duration.count();
			std::this_thread::sleep_for(duration_t(diff));
		}

		// If the game wants to run an interface until it's finished
		// ie. no longer active
		if(watch){

			if(active_interfaces.empty() || active_interfaces.front() != watch)
				return;
		}
	}
}

void game::stop(){
	game_loop = false;
}

void game::load_Party(std::string fname){

	characters[WizardCat] = {"WizardCat"};
}