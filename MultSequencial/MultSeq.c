#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]) {
	FILE* matriz;
	FILE* matrizResultado;
	char* arqLoc[20];
	char num[33];
	*arqLoc = argv[1];
	int linhasA = 0, colunasA = 0, linhasB = 0, colunasB = 0;
	float tempoTotal = 0;
	
  	matriz = fopen(*arqLoc, "r");
	if (matriz == NULL){
	    printf("Problemas na abertura do arquivoA\n");
	    exit(-1);
  }
	fscanf(matriz,"%d", &linhasA);
	fscanf(matriz, "%d", &colunasA);
	
	matrizResultado = fopen("matrizResultado.txt", "w");
	if (matrizResultado == NULL){  
	    printf("Problemas na abertura do arquivoB\n");
	    exit(-1);
  	}
//-escrevendo qtd de linhas da matrizResultante no arquivo -
	
	fprintf(matrizResultado, "%d ", linhasA);
	
//--------Preenchendo matriz 1--------
	

	int ** matrizA;//alocando memoria para M1
  	matrizA = malloc( linhasA * sizeof(int*));
  	for (int i = 0; i < linhasA; i++){
    	matrizA[i] = malloc( colunasA * sizeof(int));
  	}
	
	for(int i = 0; i < linhasA; i++){
		for(int j = 0; j < colunasA;j++){
			matrizA[i][j] = 0;
			fscanf(matriz, "%i", &matrizA[i][j]);
		}
	}

	fclose(matriz);

//-escrevendo a qtd de colunas da matrizResultante no arquivo -
	*arqLoc = argv[2];
	matriz = fopen(*arqLoc, "r");
	fscanf(matriz,"%d", &linhasB);
	fscanf(matriz, "%d", &colunasB);

	fprintf(matrizResultado, "%d ", colunasB);
	fprintf(matrizResultado, "\n");

//--------Preenchendo matriz 2--------
	int ** matrizB;
	
  	matrizB = malloc( linhasB * sizeof(int*));
  	for (int i = 0; i < linhasB; i++){
    	matrizB[i] = malloc( colunasB * sizeof(int));
  	}
	
	for(int i = 0; i < linhasB; i++){
		for(int j = 0; j < colunasB;j++){
			matrizB[i][j] = 0;
			fscanf(matriz, "%i", &matrizB[i][j]);
		}
	}
//-------Executando a multiplicação------
	
	
	int soma = 0; 
	
	for(int i = 0; i < linhasA; i++) {
		for(int j = 0; j < colunasB; j++) {
			
			float tempoDaCelula = 0;
			time_t begin = time(NULL);
			
			for(int x = 0; x < colunasA; x++) {
				soma +=  matrizA[i][x] * matrizB[x][j];
			}
			//printf("\n");
			
			time_t end = time(NULL);
			tempoDaCelula = end - begin;
			//printf("tempo dessa celula: %f\n",tempoDaCelula);
			tempoTotal += tempoDaCelula;
			

//---Preenchendo o arquivo com a matrizResultante e o tempo-----
			fprintf(matrizResultado,"C%d,%d ", i+1,j+1);
			
			fprintf(matrizResultado, "%d ", soma);

			fprintf(matrizResultado, "%.2f \n", tempoDaCelula);

			soma = 0;
		}
		
	}

	fprintf(matrizResultado, "%.2f ", tempoTotal);
	printf("%.2f \n", tempoTotal);

	fclose(matriz);
	fclose(matrizResultado);
	
	for(int i = 0; i < linhasA ; i++ ){
    	free(matrizA[i]);
    	free(matrizB[i]);
  	}

	free(matrizA);
	free(matrizB);
  	return 0;
}