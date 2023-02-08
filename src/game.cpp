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
	MainMenu.Game = this;

	MessageBox.Game = this;
	MessageBox.openFile("data/dialogue");

	InputBox.Game = this;

	WorldMap.Game = this;

	video::init();
	video::create_Window("RPG Test", 640, 480);

	input::init();

	audio::init();
}

void game::load_Return(){

	if(active_interfaces.empty())
		return;

	interface* caller = active_interfaces.front();
	active_interfaces.pop_front();

	if(active_interfaces.empty())
		return;

	interface* handler = active_interfaces.front();

	if(caller->callback && handler)
		caller->callback(handler);

	caller->callback = NULL;
}

void game::load_MainMenu(callbackFn callback){
	MainMenu.callback = callback;
	active_interfaces.clear();
	active_interfaces.push_front(&MainMenu);
}

void game::load_MessageBox(std::string section, callbackFn callback){
	MessageBox.gotoSection(section.c_str());
	MessageBox.callback = callback;
	active_interfaces.push_front(&MessageBox);
}

void game::load_InputBox(callbackFn callback){
	InputBox.callback = callback;
	active_interfaces.push_front(&InputBox);
}

void game::load_WorldMap(std::string map, callbackFn callback){
	WorldMap.load_Map(map);
	WorldMap.callback = callback;
	active_interfaces.clear();
	active_interfaces.push_front(&WorldMap);
}

void game::run(){

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
			active_interfaces.front()->update();

		// Draw from bottom to top
		video::clear_Buffer(255, 255, 255, 255);

		for(std::list<interface*>::reverse_iterator it = active_interfaces.rbegin(); it != active_interfaces.rend(); it ++)
			(*it)->draw();

		video::swap_Buffer();

		// Calculate delta time and sleep if needed
		// to achieve the desired FPS
		time_t time_end = clock::now();
		duration_t duration = std::chrono::duration_cast<duration_t>(time_end - time_start);

		if(duration.count() < seconds_per_frame * 1000.){
			double diff = seconds_per_frame * 1000. - duration.count();
			std::this_thread::sleep_for(duration_t(diff));
		}
	}
}

void game::stop(){
	game_loop = false;
}