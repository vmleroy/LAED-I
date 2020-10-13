/****************

LAED1 - Problema da Mochila

Alunos(as): Victor Le Roy Matos

Data: 18/09

****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Estrutura designada para guardar informacoes dos itens apresentados
	a serem colocados ou nao nas mochilas
*/
typedef struct itens {
	int weight;
	int price;
	int onBag;
} ITEM;

/*
	Estrutura designada para preencher os items na mochila
*/
typedef struct bag {
	ITEM *itensOnBag;
	int capacity;
	int weight;
	int price;
} BAG;


//Variaveis globais
BAG BAG1;
ITEM *ITENS;
int quantityItens = 0;
int quantityItensBag = 0;

/*
	Funcoes uteis
*/

int convertToInt(char *string) {
	int number = atoi(string);
	return number;
}

int myPow(int base, int number) {
	int result = 1;
	while(number > 0) {
		result = result*base;
		number--;
	}
	return result;
}

/*
	Parte do programa de reconhecimento do arquivo lido
	e construcao das matrizes texto
*/

void printItens() {
	printf("\n");
	printf("Printando...\n");
	for(int i=0; i<quantityItens; i++) {
		printf("weight: %d, price:%d \n", ITENS[i].weight, ITENS[i].price);
	}
	printf("\n");
	for(int i=0; i<quantityItensBag; i++) {
		printf("POS = %d, Bag weight: %d, Bag price:%d \n", i, BAG1.itensOnBag[i].weight, BAG1.itensOnBag[i].price);
	}
}

void setItemsStruct (char (*stringArchive)[100], int size) {
	//Copiar uma parte da string para outra e setar os itens
	int j=0, k=0, auxQuantityItens=0, auxCopy = 0;
	int price = 0, weight = 0;
	char aux[100];
	
	//Variaveis de colocar os itens nas mochilas
	int auxItensId = 0, onbag = 0, itensOnBagPos = 0;

	for(int i=0; i<size; i++) { 
		//Setar a capacidade maxima da mochila
		if(i==0) BAG1.capacity = convertToInt(stringArchive[i]);

		//Setar a quantidade de itens no problema
		else if(i==1) {
			quantityItens = convertToInt(stringArchive[i]);
			ITENS = malloc(sizeof(ITEM) * quantityItens);
			BAG1.itensOnBag = malloc(sizeof(ITEM) * quantityItens);
			memset(ITENS, '\0', sizeof(ITEM) * quantityItens);
			memset(BAG1.itensOnBag, '\0', sizeof(ITEM) * quantityItens);
		}

		//Preencher informacoes dos itens
		else if(quantityItens > auxQuantityItens) {
			auxCopy=0; k=0; j=0; memset(aux, '\0', sizeof(aux));
			while(stringArchive[i][j]!='\0') {
				if(auxCopy == 1) {
					if(stringArchive[i][j] != '\n') {
						aux[k] = stringArchive[i][j];
						k++;
					}
				}
				if(stringArchive[i][j] == ' ') auxCopy = 1;							
				j++;

			}			
			weight = convertToInt(stringArchive[i]);
			price = convertToInt(aux);
			ITENS[auxQuantityItens].weight = weight;
			ITENS[auxQuantityItens].price = price;					
			auxQuantityItens++;
		}

		//Verificar quais itens estao na mochila		
		else if (auxQuantityItens >= quantityItens) {			
			j=0;
			if( (stringArchive[i][j] != '\n') && (stringArchive[i][j] != '\0') ) {
				onbag = convertToInt(stringArchive[i]);
				ITENS[auxItensId].onBag = onbag;
				if(onbag == 1) {
					BAG1.itensOnBag[itensOnBagPos].weight = ITENS[auxItensId].weight;
					BAG1.itensOnBag[itensOnBagPos].price = ITENS[auxItensId].price;					
					//printf("POS = %d, Bag weight: %d, Bag price:%d \n", itensOnBagPos, BAG1.itensOnBag[itensOnBagPos].weight, BAG1.itensOnBag[itensOnBagPos].price);
					itensOnBagPos++;
				}
				auxItensId++;
			}
		}

	}
	quantityItensBag = itensOnBagPos;
	//printItens();
}

void readArchive (FILE *archive) { 
	char *auxString;
	int linha = 0;
	auxString = malloc(sizeof(char)*100);

	//Contabilizando quantas linhas existem
	while(fgets(auxString, 100, archive) != NULL) {
		linha++;
	}

	//Setando a linha do arquivo pra o inicio
	fseek(archive, 0, SEEK_SET);
	char stringArchive[linha][100];
	int i = 0;

	while(fgets(auxString, 100, archive) != NULL) {
		//Criando uma matriz auxiliar para conter as informacoes do texto
		strcpy(stringArchive[i], auxString);
		i++;
	}

	setItemsStruct(stringArchive,linha);
}


void archiveInfo (char* archiveName) {
	FILE *archive = fopen(archiveName, "r");
	
	if(archiveName == NULL) printf("ERROR! Archive couldnt be open.\n");
	else {
		readArchive(archive);
	}

	fclose(archive);
}

/*
	Parte do programa para tratar do problema da mochila
	criando matriz binaria e comparando se otimo, viavel ou inviavel
*/

void printSolution(int binaryMatrix[][quantityItens], int solutionArray[][2], int row, int maxValor) {
	for(int i=0; i<row; i++) {
		for(int j=0; j<quantityItens; j++) {
			printf("%d", binaryMatrix[i][j]);
		}
		printf(" %d	%d ", solutionArray[i][0], solutionArray[i][1]);
		if(solutionArray[i][0]>BAG1.capacity) printf("inviavel\n");
		else if(solutionArray[i][1]==maxValor && solutionArray[i][0]<=BAG1.capacity) printf("otimo\n");
		else printf("viavel\n");
	}
}

int bagWeightAndPrice() {
	//Descobre se o caso da mochila e otimo, viavel ou inviavel, se for inviavel retorna 0
	for(int i=0; i<quantityItensBag; i++) {
		BAG1.weight += BAG1.itensOnBag[i].weight;
		BAG1.price += BAG1.itensOnBag[i].price;
	}

	if(BAG1.weight > BAG1.capacity) return 0;
	else return 1;
}


void createBinaryMatrix(int binaryMatrix[][quantityItens], int rows) {
	//Criando a matriz binaria
	for(int i=0; i<rows; i++) {
		for(int j=0; j<quantityItens; j++) {
			if(j!=quantityItens-1) binaryMatrix[i][j] = (i >> ((quantityItens - 1) - j )) & 0x1;
			else binaryMatrix[i][j] = i & 0x1;
		}
	}
}

int solveProblem(int binaryMatrix[][quantityItens], int rows) {
	//Matriz solucao, cada linha representa soma do peso(0) e valor(1)
	int solutionArray[rows][2];
	//Variaveis para encontrar soma do peso e do valor
	int sPeso = 0, sValor = 0;
	
	//Percorre a matriz binaria e seta uma tabela resposta
	for(int i=0; i<rows; i++) {
		for(int j=0; j<quantityItens; j++) {
			if(binaryMatrix[i][j] == 1) {
				sPeso += ITENS[j].weight;
				sValor += ITENS[j].price;
			}
		}
		solutionArray[i][0] = sPeso;
		solutionArray[i][1] = sValor;
		// printf("PESO %d\n", soluctionArray[i][0]);
		// printf("VALOR %d\n", soluctionArray[i][1]);
		sPeso = 0;
		sValor = 0;
	}

	//Procura valor maximo entre os pesos viaveis para encontrar os casos otimos
	int maxValor = 0;
	//int maxPeso = 0;
	for(int i=0; i<rows; i++) {
		if( (solutionArray[i][0] <= BAG1.capacity) && (maxValor <= solutionArray[i][1]) ) {
			maxValor = solutionArray[i][1];
			//maxPeso = solutionArray[i][0];
		}
	}

	
	//printf("Peso mochila = %d, pesoValor = %d\n", BAG1.weight, maxPeso);
	//printf("Valor mochila = %d, maxValor = %d\n", BAG1.price, maxValor);	
	//printSolution(binaryMatrix, solutionArray, rows, maxValor);

	//Decide se o caso da mochila e viavel ou nao, 1 para otimo, 0 para viavel
	if(maxValor == BAG1.price) return 1;
	else return 0;
}


int main(){
	char archiveName[100];
	printf("Digite o nome do arquivo: ");
	scanf("%s", archiveName);
	archiveInfo(archiveName);

	//printf("Bag capacity = %d\n", BAG1.capacity);
	//printf("items = %d, bag = %d\n", quantityItens, quantityItensBag);
	// printf("\n");

	if(bagWeightAndPrice() == 0) printf("Solucao inviavel.\n");
	else {
		int rows = myPow(2, quantityItens);
		int binaryMatrix[rows][quantityItens];
		createBinaryMatrix(binaryMatrix, rows);
		if(solveProblem(binaryMatrix, rows) == 1) printf("Solucao otima.\n");
		else printf("Solucao viavel mas nao otima.\n");
	}
}