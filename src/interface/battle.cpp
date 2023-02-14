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
				Game->Party[i]->status,
				{320, 240}
			};
			player.work.set(0.5, {action::intro, {480 + i * 16 - 320, 64 + i * 80 - 240}});
			actors.push_back(player);
		}
	}

	actor enemy = {
		&Game->Enemies[game::enemies::slime],
		Game->Enemies[game::enemies::slime].stats,
		{16, 200}
	};
	enemy.work.set(1, {action::intro, {}});
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

				if(actor.work.done()){

					if(actor.work.get().type == action::intro)
						actor.position += actor.work.get().transition;

					actor.work.reset();
				
				}else{

					if(actor.work.get().type == action::intro)
						actor.work.increment(Game->delta_Time());

					if(!next || actor.who->status.spd > next->who->status.spd)
						next = &actor;
				}
			}

			if(next){

				if(next->work.get().type != action::intro)
					next->work.increment(Game->delta_Time());

			}else{
				mode = inputting_actions;
			}

			break;
		}

		case inputting_actions: {

			actor* next = NULL;

			for(auto& actor : actors){

				if(actor.work.done()){

					if(!next || actor.who->status.spd > next->who->status.spd)
						next = &actor;
				}
			}

			if(next){

				if(Game->is_Enemy(next->who))
					next->work.set(0.2, {action::attack, {0, 0}});

				if(Game->is_PartyMember(next->who)){

					if(Game->key_Pressed(SDL_SCANCODE_UP)){
						cursor ++;

						if(cursor >= actors.size())
							cursor = 0;
					}

					if(Game->key_Pressed(SDL_SCANCODE_DOWN)){
						cursor --;

						if(cursor < 0)
							cursor = actors.size()-1;
					}

					if(Game->key_Pressed(SDL_SCANCODE_SPACE)){
						next->work.set(0.2, {action::attack, {0, 0}});
					}
				}
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
			Game->draw_Text(actors[cursor].position.x+64, actors[cursor].position.y, "<-", "DotGothic16-Regular.ttf", 26);
			break;
	}

	for(auto& actor : actors){

		point pos = actor.position;

		switch(actor.work.get().type){

			case action::intro: {
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