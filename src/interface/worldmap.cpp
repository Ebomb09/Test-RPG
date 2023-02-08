#include <cstring>
#include <fstream>
#include <string>
#include <iostream>
#include "interface/worldmap.h"

void worldmap::update(){

}

void worldmap::draw(){

}

bool worldmap::load_Map(std::string map){

	// Open file
	std::fstream file(map, std::ios_base::in);

	if(file.fail()){
		file.close();
		return false;
	}

	while(!file.eof()){
		std::string str;
		std::getline(file, str);

		char tag[80]; 
		char tag2[80];

		int c = std::sscanf(str.c_str(), "<%79s%*[^>]>%*[^<]</%79[^>]>", tag, tag2);

		if(std::strcmp(tag, tag2) != 0)
			continue;

		if(std::strcmp(tag, "npc") == 0){
			object npc;
			int count = std::sscanf(str.c_str(), "<%*s>%*[^<]</%79[^>]>", npc.data);

			if(count == 1)
				objects.push_back(npc);

			std::cout << count;
		}
	}

	file.close();

	return true;
}