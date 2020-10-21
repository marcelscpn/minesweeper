#include "minunittest.h"
#include <stdarg.h>
#include <stdlib.h>

int assert_array_eq(int num, int size, int type, ...){
	va_list valist;
	va_start(valist, type);
	void** ptr = (void**)malloc(num*sizeof(void*));
	for(int i = 0; i < num; i++){
		*(ptr + i) = va_arg(valist, void*);
	}
	for(int j = 0; j < size; j++){
		for(int i = 1; i < num; i++){
			switch(type){
				case 1:
					if(*(*((int**)ptr + i) + j) != *(*((int**)ptr + 0) + j)) {
						va_end(valist);
						return 1;
					}
					break;
				case 2: 
					if(*(*((char**)ptr + i) + j) != *(*((char**)ptr + 0) + j)){
						va_end(valist);
						return 1;
					}
					break;
			}
		}
	}
	va_end(valist);
	return 0;
}


