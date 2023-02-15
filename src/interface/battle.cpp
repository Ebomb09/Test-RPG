#include "interface/battle.h"
#include "game.h"
#include <cmath>

void battle::set(game* Game){

	mode = waiting_to_complete;

	actors.clear();

	for(int i = 0; i < game::characters::maxpartysize; i ++){

		if(Game->Party[0]){
			actor player = {
				Game->Party[0],
				Game->Party[0]->status,
				{320, 240}
			};
			player.work.set(0.25, {action::move, {480 + i * 16 - 320, 64 + i * 80 - 240}});
			actors.push_back(player);
		}
	}

	actor enemy = {
		&Game->Enemies[game::enemies::slime],
		Game->Enemies[game::enemies::slime].stats,
		{16, 200}
	};
	enemy.work.set(0.25, {action::move, {}});
	actors.push_back(enemy);
}

bool battle::get(){
	return true;
}

void battle::reset_Cursor(int mode, int position){
	curse.mode = mode;
	curse.position = position;
}

void battle::return_Cursor(){

	if(!next)
		return;

	switch(curse.mode){

		case cursor::select_target: {
			reset_Cursor(cursor::select_attack, curse.attack);
			break;
		}
	}	
}

void battle::select_Cursor(){

	if(!next)
		return;

	switch(curse.mode){

		case cursor::select_attack: {
			curse.attack = curse.position;

			reset_Cursor(curse.select_target);
			break;
		}

		case cursor::select_target: {
			curse.target = curse.position;
			next->work.set(0.5, {action::attack, {}});

			reset_Cursor(cursor::select_attack);
			break;
		}
	}	
}

void battle::move_Cursor(point transition){

	if(!next)
		return;

	switch(curse.mode){

		case cursor::select_attack: {
			int moves = next->who->learned_moves.size();

			curse.position += transition.y;

			if(curse.position < 0)
				curse.position = moves-1;

			if(curse.position >= moves)
				curse.position = 0;

			break;
		}

		case cursor::select_target: {

			point pos = actors[curse.position].position;
			int closest = -1;

			for(int i = 0; i < actors.size(); i ++){

				bool passed = false;

				if(transition.x > 0){
					passed = pos.x < actors[i].position.x;

				}else if(transition.x < 0){
					passed = pos.x > actors[i].position.x;

				}else if(transition.y > 0){
					passed = pos.y < actors[i].position.y;

				}else if(transition.y < 0){
					passed = pos.y > actors[i].position.y;
				}

				if(passed){

					if(closest == -1 || (pos - actors[i].position).distance() < (pos - actors[closest].position).distance())
						closest = i;
				}
			}

			if(closest != -1)
				curse.position = closest;

			break;
		}
	}
}

void battle::draw_Cursor(game* Game){

	if(!next || !Game->is_PartyMember(next->who))
		return;

	switch(curse.mode){
		
		case cursor::select_attack: {
			std::vector<move*>& moves = next->who->learned_moves;

			for(int i = 0; i < moves.size(); i ++){

				Game->draw_Text(
					320, 
					240+26*i, 
					moves[i]->name, 
					"DotGothic16-Regular.ttf", 
					26
					);
			}

			Game->draw_Text(
				480, 
				240+26*curse.position, 
				"<-", 
				"DotGothic16-Regular.ttf", 
				26
				);

			break;
		}

		case cursor::select_target: {

			Game->draw_Text(
				actors[curse.position].position.x + 64, 
				actors[curse.position].position.y, 
				"<-", 
				"DotGothic16-Regular.ttf", 
				26);	

			break;
		}
	}
}

void battle::update(game* Game){

	switch(mode){

		case waiting_to_complete: {

			next = NULL;

			for(auto& actor : actors){

				if(actor.work.done()){

					if(actor.work.get().type == action::move)
						actor.position += actor.work.get().transition;

					actor.work.reset();
				
				}else if(!next || actor.who->status.spd > next->who->status.spd){
					next = &actor;
				}
			}

			if(next){
				next->work.increment(Game->delta_Time());

			}else{
				reset_Cursor(cursor::select_attack);
				mode = inputting_actions;
			}

			break;
		}

		case inputting_actions: {

			next = NULL;

			for(auto& actor : actors){

				if(actor.work.done()){

					if(!next || actor.who->status.spd > next->who->status.spd)
						next = &actor;
				}
			}

			if(next){

				if(Game->is_PartyMember(next->who)){
					
					if(Game->key_Pressed(SDL_SCANCODE_UP))
						move_Cursor({0, -1});

					if(Game->key_Pressed(SDL_SCANCODE_DOWN))
						move_Cursor({0, 1});

					if(Game->key_Pressed(SDL_SCANCODE_RIGHT))
						move_Cursor({1, 0});

					if(Game->key_Pressed(SDL_SCANCODE_LEFT))
						move_Cursor({-1, 0});

					if(Game->key_Pressed(SDL_SCANCODE_SPACE))
						select_Cursor();

					if(Game->key_Pressed(SDL_SCANCODE_ESCAPE))
						return_Cursor();

				}else{
					next->work.set(0.5, {action::attack});
				}

			}else{
				mode = waiting_to_complete;
			}

			break;
		} 
	}

	// Check if there are any party members left
	bool lost = true;
	bool win = true;

	for(int i = 0; i < actors.size(); i ++){

		if(Game->is_PartyMember(actors[i].who))
			lost = false;
		else
			win = false;
	}

	if(lost || win || Game->key_Pressed(SDL_SCANCODE_LCTRL))
		Game->load_Return();
}

void battle::draw(game* Game){

	switch(mode){

		case waiting_to_complete:
			Game->draw_Text(0, 440, "WAITING_TO_COMPLETE", "DotGothic16-Regular.ttf", 13);
			break;

		case inputting_actions:
			Game->draw_Text(0, 440, "INPUTTING_ACTIONS", "DotGothic16-Regular.ttf", 13);
			draw_Cursor(Game);

			if(next){
				Game->draw_Colour(255, 0, 0, 255);
				Game->draw_Rectangle(next->position.x, next->position.y, 64, 64);
			}
			break;
	}

	for(auto& actor : actors){

		point pos = actor.position;

		switch(actor.work.get().type){

			case action::move: {
				pos += actor.work.get().transition * actor.work.percent();
				pos.y -= 120 * std::sin(M_PI * actor.work.percent());
				break;
			}

			case action::attack:{
				pos.x -= 30 * std::cos(M_PI * 1.5 + M_PI * actor.work.percent());
				break;
			}
		}

		Game->draw_TextureClip(
			pos.x, pos.y,
			0, 0,
			32, 32,
			2, 2,
			actor.who->asset
			);

		Game->draw_Text(
			pos.x, pos.y + 64,
			"Health" + std::to_string(actor.status.hp),
			"DotGothic16-Regular.ttf",
			13
			);
	}


}