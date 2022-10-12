#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_RANGE 100

void carregaMatriz(char nomeArq[20], int linhas, int colunas) {
	FILE *matriz;
	matriz = fopen(nomeArq, "wt");
	
	if (matriz == NULL) {
		printf("Problemas na criação do arquivo\n");
		exit(-1);
	}
	char num[4];
	
	sprintf(num, "%d", linhas);
	fprintf(matriz, "%s", num);
	fprintf(matriz, "\n");
	sprintf(num, "%d", colunas);
	fprintf(matriz, "%s", num);
	fprintf(matriz, "\n");
	
	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			
			int numRandom = (int)rand() % MAX_RANGE;
			
			sprintf(num, "%d", numRandom);
			fprintf(matriz, "%s", num);
			
			if(j == colunas - 1 && i == linhas -1){
				break;
			}
			fprintf(matriz, "\n");
		}
	}
	fclose(matriz);
}

int main(int argc, char *argv[]) {
	int n1 = atoi(argv[1]);
	int m1 = atoi(argv[2]);
	int n2 = atoi(argv[3]);
	int m2 = atoi(argv[4]);

	if(m1 != n2){
		printf("A quantidade de colunas da primeira matriz deve ser igual a quantidade de linhas da segunda matriz.\n");
		exit(-1);
	}
	
	srand(time(NULL));
	
	carregaMatriz("matriz1.txt", n1, m1);
	carregaMatriz("matriz2.txt", n2, m2);
  	return 0;
}