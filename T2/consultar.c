#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void line_analysis(char *s,FILE *in2,char *izq,char *der,char *key,char *value){

	//FILE *in;
	//, *out;
	//printf("Abriendo archivo %s ...\n", s);
	//in= fopen(s, "r");
	//out= fopen(s, "w");

	int i=1;
	//char izq[11];
	//char der[11];
	//char key[21];
	//char value[60];
	char aux='a';

	//aux=getc(in);
	//printf("Aux= %c \n", aux);

	int save=1;
	for(i=0;i<10;i++){
		aux=getc(in2);
		if(aux==' '){
			izq[i]='\0';
			save=0;
		}
		if(save==1){
			izq[i]=aux;	
		}
		
	}
	save=1;
	for(i=0;i<10;i++){
		aux=getc(in2);
		if(aux==' '){
			der[i]='\0';
			save=0;
		}
		if(save==1){
			der[i]=aux;
		}
		
	}

	save=1;
	for(i=0;i<20;i++){
		aux=getc(in2);
		//key[i]=aux;
		if(aux==' '){
			key[i]='\0';
			save=0;
		}
		if(save==1){
			key[i]=aux;
		}
	}
	//key[i]='\0';

	save=1;
	for(i=0;i<60;i++){
		aux=getc(in2);
		value[i]=aux;		
	}
	value[i]='\0';

	if(ferror(in2)){
		printf("ERROR!\n");
	}

	//fclose(in);
	//fclose(out);	

	//printf("Izq  : %s\n", izq);
	//printf("Der  : %s\n", der);
	//printf("Key  : %s\n", key);
	//printf("Value: %s\n", value);

	//printf("KEY: %s|\n", key);
	
	//char *out={izq,der,key,value};
	//return out;
}



int main(int argc, char **argv) {
	
	char *target=argv[2];
	//printf("Buscando: %s\n", target);
	FILE *in2;
	//printf("Abriendo archivo %s ...\n", argv[1]);
	in2= fopen(argv[1], "r");

	char izq[11];
	char der[11];
	char key[21];
	char value[60];

	line_analysis(argv[1],in2,izq,der,key,value);

	//printf("Izq  : %s\n", izq);
	//printf("Der  : %s\n", der);
	//printf("Key  : %s\n", key);
	//printf("Value: %s\n", value);

	//fseek(in2, 200, SEEK_SET);
	
	int condicion=1;
	int next_line=0;
	while(condicion){
		if(strcmp(target,key)==0){
			printf("%s\n",value);
			break;
		}
		if(strcmp(target,key)>0){
			next_line=atoi(der);
			next_line=next_line*100;
			//printf("Avanza a nodo derecho: %d\n",next_line);
		}
		if(strcmp(target,key)<0){
			next_line=atoi(izq);
			next_line=next_line*100;
			//printf("Avanza a nodo izquierdo: %d\n",next_line);
		}

		if(next_line<0){
			printf("palabra no encontrada\n");
			break;
		}
		fseek(in2, next_line, SEEK_SET);

		line_analysis(argv[1],in2,izq,der,key,value);

		//printf("Izq  : %s\n", izq);
		//printf("Der  : %s\n", der);
		//printf("Key  : %s\n", key);
		//printf("Value: %s\n", value);

	}
	fclose(in2);

	return 0;
}