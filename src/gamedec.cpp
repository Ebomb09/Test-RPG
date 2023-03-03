#include "game.h"

void game::load_Party(std::string fname){

	Characters[characters::wizardcat] = character(
		"WizardCat",
		"data/textures/WizardCat.png", 
		{100, 5, 10, 2, 4, 10},
		{&Moves[moves::attack], &Moves[moves::item], &Moves[moves::thunder]}
	);

	Characters[characters::dragonknight] = character(
		"DragonKnight",
		"data/textures/DragonKnight.png", 
		{100, 12, 4, 10, 5, 10},
		{&Moves[moves::attack], &Moves[moves::item], &Moves[moves::fire]}
	);

	Characters[characters::fireguy] = character(
		"FireGuy",
		"data/textures/FireGuy.png", 
		{100, 1, 20, 5, 5, 20},
		{&Moves[moves::attack], &Moves[moves::item], &Moves[moves::fire]}
	);
}

void game::load_Enemies(){
	
	Enemies[enemies::slime] = character(
		"Slime",
		"data/textures/slime.png",
		{100, 2, 3, 1, 2, 4},
		{&Moves[moves::fire]}
	);
}

void game::load_Moves(){

	Moves[moves::attack] = move(
		"Attack",
		"data/textures/attack.fx",
		{
			{statistics::STR, -1.0, statistics::HP}
		}
	);

	Moves[moves::item] = move(
		"Item",
		"data/textures/item.fx"
	);

	Moves[moves::ice] = move(
		"Ice",
		"data/textures/ice.fx",
		{
			{statistics::HP, -0.5, statistics::HP},
			{statistics::MAG, -1.0, statistics::HP},
			{statistics::MAG, -0.2, statistics::SPD}
		}
	);

	Moves[moves::fire] = move(
		"Fire",
		"data/textures/fire.fx",
		{
			{statistics::STR, -0.65, statistics::HP},
			{statistics::MAG, -1.2, statistics::HP}
		}
	);

	Moves[moves::thunder] = move(
		"Thunder",
		"data/textures/ice.fx",
		{
			{statistics::SPD, -0.65, statistics::HP},
			{statistics::MAG, -1.1, statistics::HP}
		}
	);
}