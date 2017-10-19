#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include "bolsa.h"

char comprador_actual[100];
char mejor_vendedor[100];
int mejor_precio = INT_MAX;
pthread_mutex_t mutex;
pthread_cond_t cond;

int vendo(int precio, char *vendedor, char *comprador){
	
	pthread_mutex_lock(&mutex);

	if(precio>=mejor_precio){
		pthread_mutex_unlock(&mutex);
		return 0;		
	}
	else{
		strcpy(mejor_vendedor, vendedor);
		mejor_precio=precio;
		pthread_cond_broadcast(&cond);

		pthread_cond_wait(&cond, &mutex);

		if(*comprador_actual=='\0'){
			pthread_mutex_unlock(&mutex);
			return 0;		
		}
		else{
			strcpy(comprador, comprador_actual);
			*comprador_actual ='\0';
			*mejor_vendedor ='\0';
			mejor_precio=INT_MAX;
			pthread_mutex_unlock(&mutex);
			return 1;
		}
	}	
}

int compro(char *comprador, char *vendedor){

	pthread_mutex_lock(&mutex);
	if (*mejor_vendedor == '\0') {
		pthread_mutex_unlock(&mutex);
		return 0;
	}
	strcpy(vendedor, mejor_vendedor);
	strcpy(comprador_actual, comprador);
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	return mejor_precio;
	
}


