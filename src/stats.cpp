#include "stats.h"

int* statistics::get_stat(name stat){

	switch(stat){
		case name::HP: return &hp;
		case name::STR: return &str;
		case name::MAG: return &mag;
		case name::VIT: return &vit;
		case name::SPR: return &spr;
		case name::SPD: return &spd;
	};
	return NULL;
}