#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t1.h"

uint insertar_bits(uint x, int pos, uint y, int len) {
  	
	uint mask1=0;
	
	int i;
	for(i=1;i<=pos;i++){
		mask1<<=1;
		mask1=mask1+1;
	}
	printf("%i\n",mask1);
	uint mask2=~mask1;
	printf("%i\n",mask2);


	uint xa = x&mask2;
	uint xb = x&mask1;

	printf("El x original: %i\n",x);
	printf("El x con mascara 2: %i\n",xa);
	printf("El x con mascara 1: %i\n",xb);

	xa<<=len;
	y<<=pos;

	uint out = xa+y+xb;
	printf("Output: %i\n",out);
	return out;
}


void eliminar_espacios(char *s) {
  
}
