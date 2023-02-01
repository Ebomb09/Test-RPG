#ifndef GAME_PAGE_H
#define GAME_PAGE_H

#include <tuple>

template <class T, class Tid, int size>
struct page{

	std::tuple<T, Tid, int> elements[size];

	page(){

		for(int i = 0; i < size; i ++){
			std::get<0>(elements[i]) = NULL;
			std::get<1>(elements[i]) = Tid{};
			std::get<2>(elements[i]) = 0;
		}
	}

	T find(Tid id){

		for(int i = 0; i < size; i ++){

			if(std::get<1>(elements[i]) == id){
				std::get<2>(elements[i]) ++;
				return std::get<0>(elements[i]);
			}
		}

		return NULL;
	}

	T replace(T next, Tid id){
		int smallest = 0;

		for(int i = 0; i < size; i ++){

			if(std::get<2>(elements[i]) < std::get<2>(elements[i])){
				smallest = i;
			}
		}

		T old = std::get<0>(elements[smallest]);
		std::get<0>(elements[smallest]) = next;
		std::get<1>(elements[smallest]) = id;
		std::get<2>(elements[smallest]) = 0;
		return old;
	}

};

#endif