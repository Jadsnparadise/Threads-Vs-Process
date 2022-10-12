#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int ** matrizA;//alocando memoria para MA
int ** matrizB;//alocando memoria para MB

int linhasA, colunasA, linhasB, colunasB;

int p;

int status;

void *thread_return;

void* multThreads(void *threadIndex){
    char arqLoc[32];

    FILE* matrizResultado;
    int soma = 0;
    int index = 0;
    index = (int)(size_t)threadIndex;

    int qtdCelulasPorProcesso = (linhasA * linhasB) / p;
    int startLinha = (((linhasA * colunasB) / p)*index)/ linhasA;
    int endLinha = (((linhasA * colunasB) / p)*(index+1))/ linhasA;

    //printf("linhasA = %d colunasA = %d linhasB = %d colunasB = %d index = %d p = %d\n",linhasA,colunasB,linhasB,colunasB,index,p);
    
    //printf("processo numero %d, começo na linha: %d e termino na linha %d \n",(int)(size_t)threadIndex, startLinha,endLinha);

    sprintf(arqLoc, "%dx%d/Thread%d.txt", linhasA,colunasB,(int)(size_t)threadIndex);
    matrizResultado = fopen(arqLoc,"w");
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
            
            time_t end = time(NULL);
            
            qtdCelulasCalculadas++;
            tempoDaCelula = end - begin;
            tempoTotal += tempoDaCelula;

            fprintf(matrizResultado,"C%d,%d ", i+1,j+1);

            fprintf(matrizResultado, "%d ", soma);

            fprintf(matrizResultado, "%.2f \n", tempoDaCelula);

            soma = 0;
            if(qtdCelulasCalculadas == qtdCelulasPorProcesso){
                fprintf(matrizResultado, "%.2f \n", tempoTotal);
                printf("%.2f \n", tempoTotal);
                fclose(matrizResultado);
                pthread_exit(NULL);
            }
        }
    }	
}

int main(int argc, char *argv[]) {
    FILE* matriz;
	FILE* matrizResultado;
	char* arqLoc[32];
	*arqLoc = argv[1];
	float tempoTotal = 0;
    linhasA = 0, colunasA = 0, linhasB = 0, colunasB = 0;
	
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

//-escrevendo a qtd de colunas da matrizResultante no arquivo
	*arqLoc = argv[2];
	matriz = fopen(*arqLoc, "r");
	fscanf(matriz,"%d", &linhasB);
	fscanf(matriz, "%d", &colunasB);

	fprintf(matrizResultado, "%d ", colunasB);
	fprintf(matrizResultado, "\n");

//--------Preenchendo matriz 2--------
	
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
	p = atoi(argv[3]);//Quantidade de processos a serem criados;
	pthread_t threads[p];
    //printf("linhasA = %d colunasA = %d linhasB = %d colunasB = %d p = %d\n",linhasA,colunasB,linhasB,colunasB,p);
    for(int i = 0; i < p; i++){
        status = pthread_create(&threads[i],NULL,multThreads,(void*)(size_t) i);

        if(status != 0){
            printf("Erro %d na criação da Thread %d", status, i);
            exit(-1);
        }

    }
    
    for(int i = 0; i < p; i++){
        pthread_join(threads[i], &thread_return);
    }

	fclose(matrizResultado);
	
	for(int i = 0; i < linhasA ; i++ ){
    	free(matrizA[i]);
    	free(matrizB[i]);
  	}

    free(matrizA);
    free(matrizB);

  	return 0;
}