#include <cstddef>
#include "interface/base.h"

interface::interface() : Game(NULL), callback(NULL), args(NULL){

}

interface::~interface(){
	
	if(args)
		delete [] args;
}