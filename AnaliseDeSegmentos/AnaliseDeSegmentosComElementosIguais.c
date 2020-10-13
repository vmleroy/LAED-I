#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Variaveis globais
*/
int *intArray;
int *segmentsArray;
int **solutionArray;
int numbersToArray = 0;
int segmentsSize = 0;
int solutionSize = 0;

/*
    Funcoes uteis
*/
int convertToInt(char *string) {
	int number = atoi(string);
	return number;
}



/*
    Tratamento do arquivo
*/
void printArray() {
    printf("PRINTANDO ARRAY\n");
    for(int i=0; i<numbersToArray; i++) {
        printf("%d ", intArray[i]);
    }
    printf("\n");
}

void setArray(char **string, int linha) {
    //Criando o array
    char aux[20];
    int j = 0, k = 0, q = 0;
    memset(aux, '\0', sizeof(aux));
    for(int i=0; i<linha; i++) {    
        if(i==0) {
            numbersToArray = convertToInt(string[0]);
            intArray = (int *) calloc(numbersToArray, sizeof(int));
            // printf("string[0] = %s", string[0]);
            // printf("NUMBERSTOARRAY = %d\n", numbersToArray);
        }    
        else {
            k=0; j=0;
            while(string[i][j]!='\0') {
				if( (string[i][j] != '\n') && (string[i][j] != ' ')) {
					aux[k] = string[i][j];
					k++;
				}
                else {
                    intArray[q] = convertToInt(aux);
                    //printf("%d ", intArray[q]);
                    q++;
                    k=0;
                    memset(aux, '\0', sizeof(aux));
                }
                j++;
            }
        }
    }

    //Seta o ultimo valor
    intArray[q] = convertToInt(aux);

    //printArray();
}

//Leitura do arquivo e armazenamento do vetor
//Por ser apenas um vetor sera utilizado apenas o fgets para armazenar tudo em uma string e depois ser tratada com vetor de inteiros
void readArchive(FILE* archive) {
    char **auxString;
	int linha = 0;
    auxString = (char **) calloc (1, sizeof(char));
    auxString[linha] = (char *) calloc(600, sizeof(char));

    fseek(archive, 0, SEEK_SET);
    while(fgets(auxString[linha], 600, archive) != NULL) {
        linha++;
        auxString = (char **) realloc(auxString, (1+linha) * sizeof(auxString));
        auxString[linha] = (char *) calloc(600, sizeof(char));
    }
    
    // printf("\n");
    // for(int i=0; i<linha; i++) {
    //     //printf("i=%d %s\n", i, stringArchive[i]);
    //     printf("%s", auxString[i]);
    // }    
    // printf("\n");
    setArray(auxString, linha);
}

//Abertura de arquivo texto
void openArchive(char* archiveName) {
	FILE *archive = fopen(archiveName, "r");
	
	if(archiveName == NULL) printf("ERROR! Archive couldnt be open.\n");
	else {
		readArchive(archive);
	}

	fclose(archive);
}



/*
    Resolvendo o problema
*/
//Procurando os segmentos do vetor
void searchSegments() {
    //Setando os segmentos
    int igual = 0;
    segmentsArray = (int *) calloc(1, sizeof(int));
    for(int i=0; i<numbersToArray; i++) {
        //printf("INTARRAY[%d] = %d\n",i, intArray[i]);
        for(int j=0; j<segmentsSize; j++) {
            if(intArray[i] == segmentsArray[j]) 
                igual = 1;            
        }
        if(igual == 0) {
                segmentsArray = (int *) realloc(segmentsArray, sizeof(int) * segmentsSize + 1);
                segmentsArray[segmentsSize] = intArray[i];
                segmentsSize++;

        }
        igual = 0;
    }

    // printf("SEGMENTS\n");
    // for(int i=0; i<segmentsSize; i++) printf("%d ", segmentsArray[i]);
    // printf("\n");
    
    //Ordenando
    for(int i=0; i<segmentsSize; i++) {
        for(int j=i+1; j<segmentsSize; j++) {
            if(segmentsArray[i] > segmentsArray[j]) {
                int x = segmentsArray[j];
                segmentsArray[j] = segmentsArray[i];
                segmentsArray[i] = x;
            }
        }
    }

    // printf("SEGMENTOS ORDENADOS\n");
    // for(int i=0; i<segmentsSize; i++) printf("%d ", segmentsArray[i]);
    // printf("\n");
}

void setSolutionArray() {
    solutionArray = (int **) calloc (2, sizeof(int));
    for(int i=0; i<2; i++) solutionArray[i] = (int *) calloc(1, sizeof(int));

    //Criando a matriz solucao
    int igual = 0;
    for(int i=0; i<numbersToArray; i++) {
        //printf("INTARRAY[%d] = %d\n",i, intArray[i]);
        if((intArray[i]!=intArray[i-1]) && (i>0)) {
            solutionSize++;
            for(int k=0; k<2; k++) solutionArray[k] = (int *) realloc(solutionArray[k], 1+solutionSize*sizeof(int));
            solutionArray[0][solutionSize] = 0;
            solutionArray[1][solutionSize] = 0;
            // printf("solutionSize = %d\n", solutionSize);
        }
        for(int j=0; j<segmentsSize; j++) {
            if(intArray[i] == segmentsArray[j]) igual = 1;            
            // printf("IGUAL = %d\n", igual);
            if(igual == 1) {
                solutionArray[0][solutionSize] = j + 1;
                solutionArray[1][solutionSize] += 1;
                // printf("SOLUTIONARRAY[0][%d] = %d ", solutionSize, solutionArray[0][solutionSize]);
                // printf("SOLUTIONARRAY[1][%d] = %d\n", solutionSize, solutionArray[1][solutionSize]);
                igual = 0;
            }
        }
    }

    printf("Matriz: \n");
    for(int i=0; i<2; i++) {
        for(int j=0; j<solutionSize + 1; j++) 
            printf("%d ", solutionArray[i][j]);
    printf("\n");
    }
}




int main() {
    char archiveName[100];
	printf("Digite o nome do arquivo: ");
	scanf("%s", archiveName);
	openArchive(archiveName);

    searchSegments();
    setSolutionArray();

    free(solutionArray);
    free(segmentsArray);
    free(intArray);
}