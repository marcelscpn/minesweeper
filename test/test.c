#include "strategy.h"
#include "board.h"
#include "minunit.h"
#include <stdarg.h>

int assert_array_eq(int num, int size, int type, ...){
	va_list valist;
	va_start(valist, num);
	(void**) ptr = (void**)malloc(num*sizeof(void*));
	for(int i = 0; i < num; i++){
		*(ptr + i) = va_arg(valist, void*);
	}
	for(int j = 0; j < size; j++){
		for(int i = 1; i < num; i++){
			switch(type){
				case 1:
					if(*(*((int**)ptr + i) + j) != *(*((int**)ptr + 0) + j)) return 1;
					break;
				case 2: 
					if(*(*((char**)ptr + i) + j) != *(*((char**)ptr + 0) + j)) return 1;
					break;
			}
		}
	}
	return 0;
}

int main(void){
	return 0;
}

