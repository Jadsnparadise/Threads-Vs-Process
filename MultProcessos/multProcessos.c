#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]) {
    FILE* matriz;
	FILE* matrizResultado;
	char* arqLoc[32];
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
	fclose(matriz);

	//-------Executando a multiplicação------
	int p = atoi(argv[3]);//Quantidade de processos a serem criados;
	int soma = 0; 
	int qtdCelulasPorProcesso = (linhasA * linhasB) / p;
	pid_t pid[p];

	for(int index = 0; index < p; index++){

		pid[index] = fork();
		
		if(pid[index] < 0){
			printf("Houve um problema na criação do Processo");
			exit(-1);
		}

		else if( pid[index] == 0){
			int startLinha = (((linhasA * colunasB) / p)*index)/ linhasA;
			int endLinha = (((linhasA * colunasB) / p)*(index+1))/ linhasA;
			//printf("processo numero %d, PID = %d começo na linha: %d e termino na linha %d \n",index,getpid(), startLinha,endLinha);

			sprintf(*arqLoc, "%dx%d/Processo%d.txt", linhasA,colunasB,index);
			matrizResultado = fopen(*arqLoc,"w");
			fprintf(matrizResultado, "%d %d\n", linhasA,colunasB);
			if(matrizResultado == NULL){
				printf("Problemas na abertura do arquivoB\n");
	    		exit(-1);
		}
			int qtdCelulasCalculadas = 0;
			float tempoTotal = 0;
			for(int i = startLinha; i < endLinha; i++) {
				for(int j = 0; j < colunasB; j++) {
					
					float tempoDaCelula = 0;
					time_t begin = time(NULL);
					
					for(int x = 0; x < colunasA; x++) {
						soma +=  matrizA[i][x] * matrizB[x][j];
					}
					//printf("\n");
					
					time_t end = time(NULL);
					
					qtdCelulasCalculadas++;
					tempoDaCelula = end - begin;
					tempoTotal += tempoDaCelula;
					//printf("tempo dessa ce 
					fprintf(matrizResultado,"C%d,%d ", i+1,j+1);

					fprintf(matrizResultado, "%d ", soma);

					fprintf(matrizResultado, "%.2f \n", tempoDaCelula);

					soma = 0;
					if(qtdCelulasCalculadas == qtdCelulasPorProcesso){
						fprintf(matrizResultado, "%.2f \n", tempoTotal);
						printf("%.2f \n", tempoTotal);
						fclose(matrizResultado);

					}
				}
			
			}	

		}

		else{
			for(index = 0; index < p; index++){
				wait(NULL);
			}
		}
		
	}
	fclose(matrizResultado);
	
	for(int i = 0; i < linhasA ; i++ ){
    	free(matrizA[i]);
    	free(matrizB[i]);
  	}
  	return 0;
}