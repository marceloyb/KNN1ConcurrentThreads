// MARCELO YURI BENESCIUTTI RA 90565

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>

int linhadamatrizteste;
int natributos, nlinhasbase = 6746, nlinhasteste = 2248, nth;
float **matrizbase;
float **matrizteste;
float *min;
char buffer[50];
float distanciaMinima;

void alocamatriz(){
  int i,j;
  min = (float*)malloc(nth * sizeof(float*));
	for (i = 0; i < nth; i++)
		min[i] = 99999999999;
  matrizbase = (float**)malloc(nlinhasbase * sizeof(float*));
  matrizteste = (float**)malloc(nlinhasteste * sizeof(float*));
  for (i = 0; i < nlinhasbase; i++){
    matrizbase[i] = (float*) malloc (natributos * sizeof(float));
  }
  for (i = 0; i < nlinhasteste; i++){
    matrizteste[i] = (float*) malloc (natributos * sizeof(float));
  }
}


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

void *findmin(void *arg){
  long int i, j, linhadomenor;
  long int tid = (long int)arg;
  float soma, minlinha;
  minlinha = 9999999999999;
  
  for (i = tid; i < nlinhasbase; i+=nth){
    soma = 0;
    for (j = 0; j < natributos; j++){
      soma = soma + powf((matrizteste[linhadamatrizteste][j] - matrizbase[i][j]), 2);      
    }
    soma = sqrtf(soma);
	  if(soma < min[tid]){
      min[tid] = soma;
      linhadomenor = i;      
    }
  }
}


void paralelizado(){
  long int i, j, k;
  linhadamatrizteste = 0;
  float minimolinha;
  pthread_t *t = (pthread_t *) malloc (nth * sizeof(pthread_t));
  do{
    for(j = 0; j < nth; j++){
      pthread_create(&t[j], NULL, findmin, (void*)j);
    }
    for(j = 0; j < nth; j++){
      pthread_join(t[j], NULL);
    }
    for(k = 0; k < nth; k++){
     if(min[k] < minimolinha)
      minimolinha = min[k];
    // printf ("\nlinha %i %f\n", linhadamatrizteste+1, min[k]);
     min[k] = 9999999;
    }
    printf ("%f \n", minimolinha);
    minimolinha = 999;
    linhadamatrizteste++;
  }while(linhadamatrizteste < nlinhasteste); 
}
	
int main (int argc, char *argv[]){
  int i, j; nth = atoi(argv[1]);
  float atributoi;
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
  alocamatriz();
  for (i = 0; i < nlinhasbase; i++){
    for (j = 0; j < natributos; j++){
      atributo = get_rec(ARQUIVOBASE);
      atributoi = atof(atributo);
      matrizbase[i][j] = atributoi;
    } 
  }
  for (i = 0; i < nlinhasteste; i++){
    for (j = 0; j < natributos; j++){
      atributo = get_rec(ARQUIVOTESTE);
      atributoi = atof(atributo);
      matrizteste[i][j] = atributoi;
    }
  }
  //sequencial();
  paralelizado();
} 
