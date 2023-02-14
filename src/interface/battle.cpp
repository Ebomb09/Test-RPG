#include "interface/battle.h"
#include "game.h"
#include <cmath>

void battle::set(game* Game){

	cursor = 0;
	mode = waiting_to_complete;

	actors.clear();

	for(int i = 0; i < game::characters::maxpartysize; i ++){

		if(Game->Party[i]){
			actor player = {
				Game->Party[i],
				{320, 240}
			};
			player.action.set(0.5, {action::intro, {480 + i * 16 - 320, 64 + i * 80 - 240}});
			actors.push_back(player);
		}
	}

	actor enemy = {
		&Game->Enemies[game::enemies::slime],
		{16, 200}
	};
	enemy.action.set(1, {action::intro, {}});
	actors.push_back(enemy);
}

bool battle::get(){
	return true;
}

void battle::update(game* Game){

	switch(mode){

		case waiting_to_complete: {

			actor* next = NULL;

			for(auto& actor : actors){

				if(actor.action.done()){

					if(actor.action.get().type == action::intro)
						actor.position += actor.action.get().transition;

					actor.action.reset();
				
				}else{

					if(actor.action.get().type == action::intro)
						actor.action.increment(Game->delta_Time());

					if(!next || actor.who->stats.spd > next->who->stats.spd)
						next = &actor;
				}
			}

			if(next){

				if(next->action.get().type != action::intro)
					next->action.increment(Game->delta_Time());

			}else{
				mode = inputting_actions;
			}

			break;
		}

		case inputting_actions: {

			actor* next = NULL;

			for(auto& actor : actors){

				if(actor.action.done()){

					if(!next || actor.who->stats.spd > next->who->stats.spd)
						next = &actor;
				}
			}

			if(next){
				next->action.set(0.2, {action::attack, {0, 0}});
			}

			if(!next)
				mode = waiting_to_complete;

			break;
		} 
	}

	if(Game->key_Pressed(SDL_SCANCODE_ESCAPE))
		Game->load_Return();
}

void battle::draw(game* Game){

	switch(mode){

		case waiting_to_complete:
			Game->draw_Text(0, 440, "WAITING_TO_COMPLETE", "DotGothic16-Regular.ttf", 13);
			break;

		case inputting_actions:
			Game->draw_Text(0, 440, "INPUTTING_ACTIONS", "DotGothic16-Regular.ttf", 13);
			break;
	}

	for(auto& actor : actors){

		point pos = actor.position;

		switch(actor.action.get().type){

			case action::intro: {
				pos += actor.action.get().transition * actor.action.percent();
				pos.y -= 120 * std::sin(M_PI * actor.action.percent());
				break;
			}

			case action::attack:{
				pos.x -= 30 * std::cos(M_PI * 1.5 + M_PI * actor.action.percent());
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
			"Health" + std::to_string(actor.who->stats.hp),
			"DotGothic16-Regular.ttf",
			13
			);
	}


}