#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void line_analysis(FILE *in,char *izq,char *der,char *key,char *value){

	int i=1;
	char aux='a';
	int save=1;
	for(i=0;i<10;i++){
		aux=getc(in);
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
		aux=getc(in);
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
		aux=getc(in);
		if(aux==' '){
			key[i]='\0';
			save=0;
		}
		if(save==1){
			key[i]=aux;
		}
	}

	save=1;
	for(i=0;i<60;i++){
		aux=getc(in);
		value[i]=aux;		
	}
	value[i]='\0';

	if(ferror(in)){
		printf("ERROR!\n");
	}
}



int main(int argc, char **argv) {
	
	if (argc != 3){
		printf("Entrada invalida\n" );
		exit(1);
	}

	char *target=argv[2];
	FILE *in;
	in= fopen(argv[1], "r");

	char izq[11];
	char der[11];
	char key[21];
	char value[60];

	line_analysis(in,izq,der,key,value);
	
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
		}
		if(strcmp(target,key)<0){
			next_line=atoi(izq);
			next_line=next_line*100;
		}
		if(next_line<0){
			printf("palabra no encontrada\n");
			break;
		}

		fseek(in, next_line, SEEK_SET);
		line_analysis(in,izq,der,key,value);

	}
	fclose(in);

	return 0;
}