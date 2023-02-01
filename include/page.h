#ifndef GAME_PAGE_H
#define GAME_PAGE_H

#include <cstddef>

template <class T, class Tid, int size>
struct page{

	struct{
		T val;
		Tid id;
		int access;
	}elements[size];

	page(){

		for(int i = 0; i < size; i ++){
			elements[i].val = NULL;
			elements[i].id = Tid{};
			elements[i].access = 0;
		}
	}

	T find(Tid id){

		for(int i = 0; i < size; i ++){

			if(elements[i].id == id){
				elements[i].access ++;
				return elements[i].val;
			}
		}
		return NULL;
	}

	T replace(T next, Tid id){
		int smallest = 0;

		for(int i = 0; i < size; i ++){

			if(elements[i].access < elements[i].access){
				smallest = i;
			}
		}

		T old = elements[smallest].val;
		elements[smallest].val = next;
		elements[smallest].id = id;
		elements[smallest].access = 0;
		return old;
	}

	int count(){
		return size;
	}

	T operator[](const int index){
		return elements[index].val;
	}
};

#endif