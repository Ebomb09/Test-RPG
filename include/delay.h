#ifndef GAME_DELAY_H
#define GAME_DELAY_H

#include <iostream>

template<class type>
class delay{

	double time;
	double max_time;
	type variable;

public:
	delay() : time(0), max_time(0), variable() {}

	void increment(double delta){

		if(!done())
			time += delta;
		
		if(done())
			time = max_time;
	}

	void reset(){
		variable = type();
		max_time = 0;
	}

	bool set(double delta, type desired){

		if(done() && delta > 0){
			time = 0;
			max_time = delta;
			variable = desired;
			return true;
		}
		return false;
	}

	type& get(){
		return variable;
	}

	double percent(){

		if(max_time <= 0)
			return 0.0;

		return time / max_time;
	}

	bool done(){
		return time >= max_time;
	}
};

#endif