#include "interface/battle.h"
#include "game.h"
#include <cmath>

void battle::set(game* Game, point pos){

	start = pos;
	mode = waiting_to_complete;

	actors.clear();

	for(int i = 0; i < characters::maxpartysize; i ++){

		if(Game->Party[0]){
			actor player(
				Game->Party[0], 
				Game->Party[0]->status, 
				start, 
				0
			);

			// Define where player positions are
			action plyPos;
			plyPos.type = action::transition;
			plyPos.where = {480 + i * 16, 64 + i * 80};

			player.work.set(0.25, plyPos);
			actors.push_back(player);
		}
	}

	/* Test Single Slime Enemy */
	actor enemy(
		&Game->Enemies[enemies::slime],
		Game->Enemies[enemies::slime].stats,
		{-200,240},
		1
	);

	action enmPos;
	enmPos.type = action::transition;
	enmPos.where = {16, 200};

	enemy.work.set(0.25, enmPos);
	actors.push_back(enemy);
}

/* Get battle status / who won */
bool battle::get(){
	return true;
}

/* Copy value constructor */
actor::actor(character* _who, statistics _status, point _position, int _team){
	who = _who;
	status = _status;
	position = _position;
	team = _team;
}

/* Prcess the Actor's Work */
void actor::act(){

	// Work done so do whatever queued action
	switch(work.get().type){

		// Change position
		case action::transition: {
			position = work.get().where;
			break;
		}

		// Affect target with selected command
		case action::attack: {

			// Error Check pointers valid
			if(!work.get().command){
				std::cerr << "Error: Invalid move selected\n";
				return;
			}

			if(!work.get().target){
				std::cerr << "Error: Invalid target selected\n";
				return;			
			}

			work.get().command->deal(&status, &work.get().target->status);

			std::cout << who->name << " used " << work.get().command->name << '\n'; 

			break;
		}
	}

	work.reset();
}

/* Get first indexed character on team IF still alive */
int battle::get_IndexFirstFromTeam(int team){

	for(int i = 0; i < actors.size(); i ++)
		if(actors[i].team == team && actors[i].status.hp > 0)
			return i;

	std::cerr << "Error: No members of team " << team << " alive or found\n";
	return -1;
}

/* Reset cursor to position and select mode */
void battle::reset_Cursor(int mode, int position){
	curse.mode = mode;
	curse.position = position;

	// Default to first enemy when selecting target
	if(mode == cursor::select_target)
		curse.position = get_IndexFirstFromTeam(1);
}

/* Return cursor to previous step */
void battle::return_Cursor(){

	if(!next)
		return;

	switch(curse.mode){

		case cursor::select_target: {
			reset_Cursor(cursor::select_attack, curse.command);
			break;
		}
	}	
}

/* Create commands based on cursors current position */
void battle::select_Cursor(){

	if(!next)
		return;

	switch(curse.mode){

		case cursor::select_attack: {
			curse.command = curse.position;

			reset_Cursor(cursor::select_target);
			break;
		}

		case cursor::select_target: {
			curse.target = curse.position;

			action attack;
			attack.type = action::attack;
			attack.target = &actors[curse.target];
			attack.command = next->who->learned_moves[curse.command];

			next->work.set(0.5, attack);

			reset_Cursor(cursor::select_attack);
			break;
		}
	}	
}

/* Move cursor based on current status of selection */
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

/* Draw cursor mode */
void battle::draw_Cursor(game* Game){

	if(!next || !Game->is_PartyMember(next->who))
		return;

	Game->draw_Colour(255, 0, 0, 255);
	Game->draw_Rectangle(next->position.x, next->position.y, 64, 64);

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

				// Do not deal with the dead actors
				if(actor.status.hp <= 0)
					continue;

				// Act upon once complete or attempt speed check
				if(actor.work.done()){
					actor.act();
				
				}else if(!next || actor.who->status.spd > next->who->status.spd){
					next = &actor;
				}
			}

			// Allow actor time to do given work
			if(next){
				next->work.increment(Game->delta_Time());

			//Go to next step
			}else{
				reset_Cursor(cursor::select_attack);
				mode = inputting_actions;
			}

			// Query if there are anymore heroes / enemies alive
			int qHero = get_IndexFirstFromTeam(0);
			int qEnemy = get_IndexFirstFromTeam(1);

			if(qHero == -1 || qEnemy == -1 || Game->key_Pressed(SDL_SCANCODE_LCTRL))
				Game->load_Return();

			break;
		}

		case inputting_actions: {

			next = NULL;

			for(auto& actor : actors){

				// Do not deal with the dead actors
				if(actor.status.hp <= 0)
					continue;

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

				// Default action set for non-controllable actors
				}else{
					action defAttack;
					defAttack.type = action::attack;
					defAttack.target = &actors[0];
					defAttack.command = &Game->Moves[moves::ice];
					next->work.set(0.5, defAttack);
				}

			}else{
				mode = waiting_to_complete;
			}

			break;
		} 
	}
}

void battle::draw(game* Game){

	Game->clear_Buffer(255, 255, 255, 255);

	switch(mode){

		case waiting_to_complete:
			Game->draw_Text(0, 440, "WAITING_TO_COMPLETE", "DotGothic16-Regular.ttf", 13);
			break;

		case inputting_actions:
			Game->draw_Text(0, 440, "INPUTTING_ACTIONS", "DotGothic16-Regular.ttf", 13);
			draw_Cursor(Game);
			break;
	}

	for(auto& it : actors){

		point pos = it.position;

		// If actor is next actionable
		if(next == &it && mode == waiting_to_complete){

			switch(it.work.get().type){

				case action::transition: {
					point position = it.work.get().where;

					pos += (position - pos) * it.work.percent();
					pos.y -= 120 * std::sin(M_PI * it.work.percent());
					break;
				}

				case action::attack:{
					actor* target = it.work.get().target;
					move* command = it.work.get().command;

					int dmg = command->query_deal(statistics::HP, &it.status, &target->status);

					pos.x -= 30 * std::cos(M_PI * 1.5 + M_PI * it.work.percent());

					Game->draw_Text(
						target->position.x, target->position.y - 50 * it.work.percent(),
						std::to_string(dmg),
						"DotGothic16-Regular.ttf",
						26
						);
					break;
				}
			}
		}

		Game->draw_TextureClip(
			pos.x, pos.y,
			0, 0,
			32, 32,
			2, 2,
			it.who->asset
			);

		Game->draw_Text(
			pos.x, pos.y + 64,
			"Health " + std::to_string(it.status.hp),
			"DotGothic16-Regular.ttf",
			13
			);
	}
}