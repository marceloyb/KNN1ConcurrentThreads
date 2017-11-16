// MARCELO YURI BENESCIUTTI RA 90565

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>


char buffer[50];
float distanciaMinima;

char *get_rec(FILE *file){
	int i = 0, j;
	char c;
	for (c = fgetc(file); c != ','; c = fgetc(file)){
		if (c == EOF)
			return EOF;
    if (c == '\n'){     
     i = 0;
     c = fgetc(file);
    }
		buffer[i] = c;
    i++;
  }
  return buffer;
}

float findmin(int linhateste, int nlinhasbase, int natributos, float matrizteste[][natributos], float matrizbase[][natributos]){
  int i, j, linhadomenor;
  float soma, minlinha;
  minlinha = 9999999999999;
  for (i = 0; i < nlinhasbase; i++){
    soma = 0;
    for (j = 0; j < natributos; j++){
      soma = soma + powf((matrizteste[linhateste][j] - matrizbase[i][j]), 2);
    }
    soma = sqrtf(soma);
    if(soma < minlinha){
      minlinha = soma;
      linhadomenor = i;
    }
  }
  printf ("linha do menor %i", linhadomenor+1); 
  return minlinha;
}

void sequencial(int nlinhasteste, int nlinhasbase, int natributos, float matrizteste[][natributos], float matrizbase[][natributos]){

  int i, j, k, l;
  float soma = 0;
  for (i = 0; i < nlinhasteste; i++){
    distanciaMinima = findmin(i, nlinhasbase, natributos, matrizteste, matrizbase);
    printf ("linha %i %f\n",i+1,distanciaMinima);
  }            
}

void paralelizado(int nth, int nlinhasteste, int nlinhasbase, int natributos, float matrizteste[][natributos], float matrizbase[][natributos]){
  int i, j;
  pthread_t *t = (pthread_t *) malloc (nth * sizeof(pthread_t));
  
}
	
int main (int argc, char *argv[]){
  int i, j, nth = atoi(argv[1]);
  float atributoi;
  int natributos, nlinhasbase, nlinhasteste;
  char *atributo = malloc(sizeof(char)*50);
  char *nomearquivobase = (char*)malloc(20 * sizeof(char));
  char *nomearquivoteste = (char*)malloc(20 * sizeof(char));
 	FILE *ARQUIVOBASE;
  FILE *ARQUIVOTESTE;
  nomearquivobase = argv[2];
  nomearquivoteste = argv[3];
  ARQUIVOBASE = fopen(nomearquivobase, "r");
  ARQUIVOTESTE = fopen(nomearquivoteste, "r");
  natributos = atoi(argv[4]);
  nlinhasteste = atoi(argv[5]);
  nlinhasbase = atoi(argv[6]);
  float base[nlinhasbase][natributos];
  float teste[nlinhasteste][natributos];
  for (i = 0; i < nlinhasbase; i++){
    for (j = 0; j < natributos; j++){
      atributo = get_rec(ARQUIVOBASE);
      atributoi = atof(atributo);
      base[i][j] = atributoi;
    } 
  }
  for (i = 0; i < nlinhasteste; i++){
    for (j = 0; j < natributos; j++){
      atributo = get_rec(ARQUIVOTESTE);
      atributoi = atof(atributo);
      teste[i][j] = atributoi;
    }
  }
  sequencial(nlinhasteste, nlinhasbase, natributos, teste, base);
} 
