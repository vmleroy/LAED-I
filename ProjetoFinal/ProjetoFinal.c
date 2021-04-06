/****************

LAED1 - Projeto (Parte III) - Busca por padrão em lista

Alunos(as): Victor Le Roy Matos

Data: 17/10/2020

****************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERNSIZE      5
#define PATTERNSIZE2     11

//Texto salvo
char **auxString;
int linhasTexto = 0;
//Linhas do texto a serem salvar
int linhasPixels = 0;
//Array de inteiros das linhas do texto a serem salvas
int *intArray;
int numbersToArray = 0;
//Procurar segmento e achar solucao
int *segmentsArray;
int **solutionArray;
//Procurar padrao de pista
int patternArray[PATTERNSIZE] = {1,3,2,3,1};
//Procurar padrao faixa de pedestre preta, branca, preta, branca, preta, branca, preta, branca, preta, branca, preta, branca, preta
    //1 2 1 2 1 2 1 2 1 2 1
int faixaPatternArray[PATTERNSIZE2] = {1,2,1,2,1,2,1,2,1,2,1};
int faixaDePedestre = 0;
//Ponto medio
int *pontoMedioArray = 0;
int posicaoArrayPontoMedio = 0;

/*
    ESTRUTURA DE DADOS (LISTA ARRANJOS) - Ziviani - http://www2.dcc.ufmg.br/livros/algoritmos/implementacoes-03.php   
*/
#define INICIOARRANJO   1
#define MAXTAM          1000
typedef int TipoChave;
typedef int TipoApontador;
typedef int TipoSegmentos;
typedef int TipoNumElementos;
typedef struct {
  TipoChave Chave;
  TipoSegmentos Segmentos;
  TipoNumElementos NumElementos;
  /* outros componentes */
} TipoItem;

typedef struct {
  TipoItem Item[MAXTAM];
  TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = INICIOARRANJO;
  Lista -> Ultimo = Lista -> Primeiro;
}  /* FLVazia */

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}  /* Vazia */

void Insere(TipoItem x, TipoLista *Lista)
{ if (Lista -> Ultimo > MAXTAM) printf("Lista esta cheia\n");
  else { Lista -> Item[Lista -> Ultimo - 1] = x;
         Lista -> Ultimo++;
       }
}  /* Insere */

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ int Aux;

  if (Vazia(*Lista) || p >= Lista -> Ultimo) 
  { printf(" Erro   Posicao nao existe\n");
    return;
  }
  *Item = Lista -> Item[p - 1];
  Lista -> Ultimo--;
  for (Aux = p; Aux < Lista -> Ultimo; Aux++)
    Lista -> Item[Aux - 1] = Lista -> Item[Aux];
}  /* Retira */

void Imprime(TipoLista Lista)
{ int Aux;

  for (Aux = Lista.Primeiro - 1; Aux <= (Lista.Ultimo - 2); Aux++)
    printf("%d\n", Lista.Item[Aux].Chave);
}  /* Imprime */



/* 
    FUNCOES UTEIS
                    */
int convertToInt(char *string) {
	int number = atoi(string);
	return number;
}

/*
    CRIANDO ARRAY DE INTEROS DAS LINHAS
                                        */
void printArray() {
    printf("PRINTANDO ARRAY\n");
    for(int i=0; i<numbersToArray; i++) printf("%d ", intArray[i]);
    printf("\n");
}

void setArray(int colunas) {
    //Criando o array
    char aux[20];
    int j = 0, k = 0, q = 0;
    memset(aux, '\0', sizeof(aux));
    for(int i = colunas; i<colunas+2; i++) 
    {   if(i == (colunas) ) 
        {   numbersToArray = convertToInt(auxString[colunas]);
            //printf("NUMBERSTOARRAY = %d\n", numbersToArray);
            intArray = (int *) calloc(numbersToArray, sizeof(int));
        }    
        else 
        {   k=0; j=0;
            while(auxString[i][j]!='\0') 
            {   if( (auxString[i][j] != '\n') && (auxString[i][j] != ' ')) 
                {   aux[k] = auxString[i][j];
					k++;
				}
                else
                {   intArray[q] = convertToInt(aux);
                    q++;
                    k=0;
                    memset(aux, '\0', sizeof(aux));
                }
                j++;
            }
        }
    }
    //Seta o ultimo valor
    //intArray[q] = convertToInt(aux);
    //printArray();
}                                 

/*
    LEITURA DO ARQUIVO
                        */

void readArchive(FILE* archive) {    
    // char **auxString;
    auxString = (char **) calloc (1, sizeof(char));
    auxString[linhasTexto] = (char *) calloc(4000, sizeof(char));
    fseek(archive, 0, SEEK_SET);
    while(fgets(auxString[linhasTexto], 4000, archive) != NULL) 
    {   linhasTexto++;
        auxString = (char **) realloc(auxString, (1+linhasTexto) * sizeof(auxString));
        auxString[linhasTexto] = (char *) calloc(4000, sizeof(char));
    }
    // printf("\n");
    // for(int i=0; i<linhasTexto; i++) {
    //     printf("i=%d\n", i);
    //     printf("%s", auxString[i]);
    // }    
    // printf("\n");
    // printf("LINHA = %d\n", linhasTexto);
}

void openArchive(char* archiveName) {
	FILE *archive = fopen(archiveName, "r");
	if(archiveName == NULL) printf("ERROR! Archive couldnt be open.\n");
	else readArchive(archive);
	fclose(archive);
}

/*
    PROCURANDO SEGMENTOS
                            */
int searchSegments() {
    //Setando os segmentos
    int igual = 0, segmentsSize = 0;
    segmentsArray = (int *) calloc(1, sizeof(int));
    for(int i=0; i<numbersToArray; i++) 
    {   for(int j=0; j<segmentsSize; j++) 
            if(intArray[i] == segmentsArray[j]) igual = 1;            
        if(igual == 0) 
        {   segmentsArray = (int *) realloc(segmentsArray, sizeof(int) * segmentsSize + 1);
            segmentsArray[segmentsSize] = intArray[i];
            segmentsSize++;

        }
        igual = 0;
    }
    //Ordenando
    for(int i=0; i<segmentsSize; i++) {
        for(int j=i+1; j<segmentsSize; j++) 
        {   if(segmentsArray[i] > segmentsArray[j]) 
            {   int x = segmentsArray[j];
                segmentsArray[j] = segmentsArray[i];
                segmentsArray[i] = x;
            }
        }
    }
    return segmentsSize;
}

/*
    CRIANDO MATRIZ SOLUCAO DA LINHA PARA DESCOBRIR SE HA OU NAO PADRAO
                                                                        */
int setSolutionArray() {    
    solutionArray = (int **) calloc (2, sizeof(int));
    for(int i=0; i<2; i++) solutionArray[i] = (int *) calloc(1, sizeof(int));

    //Criando a matriz solucao
    int igual = 0, solutionSize = 0;
    int segmentsSize = searchSegments();
    for(int i=0; i<numbersToArray; i++) 
    {   if((intArray[i]!=intArray[i-1]) && (i>0)) 
        {   solutionSize++;
            for(int k=0; k<2; k++) solutionArray[k] = (int *) realloc(solutionArray[k], 1+solutionSize*sizeof(int));
            solutionArray[0][solutionSize] = 0;
            solutionArray[1][solutionSize] = 0;
        }
        for(int j=0; j<segmentsSize; j++) 
        {   if(intArray[i] == segmentsArray[j]) igual = 1;            
            if(igual == 1)
            {   solutionArray[0][solutionSize] = j + 1;
                solutionArray[1][solutionSize] += 1;
                igual = 0; 
            }
        }
    }
    // printf("Matriz: \n");
    // for(int i=0; i<2; i++) {
    //     for(int j=0; j<solutionSize + 1; j++) 
    //         printf("%d ", solutionArray[i][j]);
    // printf("\n");
    // }
    return solutionSize;
}


/*
    INSERIR PEDACO DA LINHA DE INTARRAY NA LISTA
                                                    */
TipoLista setLista(TipoLista lista, int solutionSize) {
    TipoItem item;
    for (int i = 0; i < solutionSize + 1; i++) 
    {   item.Chave = i + 1;
        item.Segmentos = solutionArray[0][i];
        item.NumElementos = solutionArray[1][i];
        Insere(item, &lista);
    }
  //Imprime(lista);
  return lista;
}                                                   

/*
    PROCURA O PONTO MEDIO CASO EXISTA PADRAO DA PISTA
                                                        */
void pontoMedio(int posicaoVermelha) {
    int posicaoMediana = 0;
    for(int i=0; i<posicaoVermelha; i++) {
        if(posicaoVermelha == i+1) 
            if( solutionArray[1][i]%2 != 0 ) posicaoMediana += solutionArray[1][i]/2;
            else posicaoMediana += (solutionArray[1][i]/2)-1;
        else posicaoMediana += solutionArray[1][i];
        //printf("posicao mediana = %d\n", posicaoMediana);
    }

    pontoMedioArray[posicaoArrayPontoMedio] = posicaoMediana;
    posicaoArrayPontoMedio++;

    //printf("Ponto Medio: %d\n", posicaoMediana);
}                                                       


/*
    PROCURANDO O PADRAO DA PISTA
                                    */
void searchPattern(TipoLista lista) {
    TipoItem item;
    int posicaoVermelha = 0;
    int j = 0, iguais = 0;
    for(int i = lista.Ultimo - 1; i >= 0; i--) 
    {   /*retira chave apontada */
        if(i>0) Retira(i, &lista, &item);
        //printf("itemSegm = %d   itemNElem = %d    pattern = %d\n", item.Segmentos, item.NumElementos, patternArray[j]);
        if(patternArray[j] != '\0') 
        {   if(item.Segmentos == patternArray[j]) 
            {   iguais = 1;
                j++;
                if(item.Segmentos == 2) posicaoVermelha = i;
            }
            else 
            {   iguais = 0;
                j = 0;
                if(item.Segmentos == patternArray[j]) 
                {   iguais = 1;
                    j++;
                }
            }            
        }
        else break;
    }
    if(iguais == 1 && j == PATTERNSIZE) { //printf("Resultado: Padrao encontrado.\n");  
                                          pontoMedio(posicaoVermelha);}
    else { //printf("Resultado: Padrao nao encontrado.\n"); 
           posicaoArrayPontoMedio++;}
}

/*
    PROCURAR FAIXA DE PEDESTRE
                                */
void faixaPattern(TipoLista lista) {
    TipoItem item;
    int j = 0, iguais = 0;
    for(int i = lista.Ultimo - 1; i >= 0; i--) 
    {   /*retira chave apontada */
        if(i>0) Retira(i, &lista, &item);
        //printf("itemSegm = %d   itemNElem = %d    pattern = %d\n", item.Segmentos, item.NumElementos, patternArray[j]);
        if(faixaPatternArray[j] != '\0') 
        {   if(item.Segmentos == faixaPatternArray[j]) 
            {   iguais = 1;
                j++;
            }
            else 
            {   iguais = 0;
                j = 0;
                if(item.Segmentos == faixaPatternArray[j]) 
                {   iguais = 1;
                    j++;
                }
            }            
        }
        else break;
    }
    if(iguais == 1 && j == PATTERNSIZE2 && faixaDePedestre == 0) faixaDePedestre = 1;  
}

/*
    PROCURANDO POR CURVA
                            */
void procurandoCurva() {
    float porcentagem = 0, numerosMaioresQueZero = 0;
    for(int i=0; i<linhasPixels;  i++) {
        if(pontoMedioArray[i] > 0) numerosMaioresQueZero++;
    }

    porcentagem = numerosMaioresQueZero/(linhasPixels-1);
    //printf("porcentagem = %f\n", porcentagem);
    if(porcentagem >= 0.7) {
        int aux = 0, difPontoMedio = 0, aux2 = 0;
        for(int i=0; i<linhasPixels;  i++) {
            if( (pontoMedioArray[i] != 0) && (aux == 0) ) { aux = pontoMedioArray[i]; break; }
        }
        for(int i=linhasPixels; i>0;  i--) {
            if( (pontoMedioArray[i] != 0) && (aux2 == 0) ) { aux2 = pontoMedioArray[i]; break; }
        }

        difPontoMedio = aux2 - aux;
        printf("difPontoMedio = %d\n", difPontoMedio);
        if( (difPontoMedio < 25 && difPontoMedio > -25) ) printf("Resultado: Pista em linha reta.\n");
        else if(difPontoMedio < (-25)) printf("Resultado: Curva a direita.\n");
        else if(difPontoMedio > 25) printf("Resultado: Curva a esquerda.\n");
    }
    else printf("Resultado: Formato da pista nao estimado.\n");
}

/*
    PROCURANDO POR PADROES DA PISTA
                                    */
void procurandoPadroes() {
    TipoLista lista;
    int solutionSize;
    linhasPixels = convertToInt(auxString[0]);
    pontoMedioArray = (int*) calloc(linhasPixels, sizeof(int));
    for(int i=1; i<linhasTexto; i+=2) {
        setArray(i);
        solutionSize = setSolutionArray(i);
        FLVazia(&lista);
        lista = setLista(lista, solutionSize);
        searchPattern(lista);
        FLVazia(&lista);
        lista = setLista(lista, solutionSize);
        faixaPattern(lista);
    }
    //procurandoCurva();
    if(faixaDePedestre == 1) printf("Resultado: Pista com faixa de pedestres\n");  
    else printf("Resultado: Pista sem faixa de pedestres\n");
}

//MAIN
int main() {
    char archiveName[100];
	printf("Digite o nome do arquivo: ");
	scanf("%s", archiveName);
	openArchive(archiveName);

    procurandoPadroes();

    //printf("posicaoArrayPontoMedio = %d\n", posicaoArrayPontoMedio);
    //printf("linhasPixels = %d\n", linhasPixels);
    //for(int j=0; j<posicaoArrayPontoMedio; j++) printf("%d ", pontoMedioArray[j]);
    free(solutionArray);
    free(segmentsArray);
    free(intArray);
}