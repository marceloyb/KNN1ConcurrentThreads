// MARCELO YURI BENESCIUTTI RA 90565

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

char buffer[50];

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

int sequencial(int *matriz){
	
}
	
int main (int argc, char *argv[]){
  int i, j;
  float atributoi;
  int natributos, nlinhas;
  char *atributo = malloc(sizeof(char)*50);
  char *nomearquivo = (char*)malloc(20 * sizeof(char));
 	FILE *ARQUIVOBASE;
  nomearquivo = argv[1]; 
  ARQUIVOBASE = fopen(nomearquivo, "r");
  natributos = atoi(argv[2]);
  nlinhas = atoi(argv[3]); 
  float base[nlinhas][natributos];
  for (i = 0; i < nlinhas; i++){
    for (j = 0; j < natributos; j++){
      atributo = get_rec(ARQUIVOBASE);
      atributoi = atof(atributo);
      base[i][j] = atributoi;    
    } 
   //get_rec(ARQUIVOBASE);
  }
  printf ("Primeiro elemento linha 2: %f \n", base[1][0]);
}
