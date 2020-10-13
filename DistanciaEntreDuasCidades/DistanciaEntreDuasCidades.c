/*
  ALGORITMO DE DIJKSTRA UTILIZADO RETIRADO DESTE SITE: https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define INFINITY 9999
#define MAX 10

void dijkstra(int G[MAX][MAX],int n,int startnode,int destiny, char cities[10][25])
{

	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;

	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
      //printf("%d\n", G[i][j]);
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];
      }
	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}

	distance[startnode]=0;
	visited[startnode]=1;
	count=1;

	while(count<n-1)
	{
		mindistance=INFINITY;

		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}

			//check if a better path exists through nextnode
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}

	//print the path and distance of each node
  int caminho[MAX];
  int tamanhoVetor = 0;
	for(i=0;i<n;i++)
		if(i!=startnode && i==destiny)
		{
			//printf("\nDistance of node%d=%d",i,distance[i]);
			//printf("\nPath=%d",i);
			j=i;
      printf("Menor percurso: ");
			do
			{
				j=pred[j];
				//printf("<-%d",j);
        caminho[tamanhoVetor] = j;
        //printf("<-%d", caminho[j]);
        tamanhoVetor++;
			}while(j!=startnode);
      for(int j=(tamanhoVetor-1);j>=0;j--)
        printf("%s ", cities[caminho[j]]);
      printf("%s\n", cities[i]);
      printf("Distancia total: %d Km\n", distance[i]);
      //printf("\n");

	}
  //printf("\n");
}

int gravacaoArquivos(char nomeArquivo[]) {
	FILE *Arquivo;
	  Arquivo = fopen(nomeArquivo,"r");
  	if (Arquivo == NULL) {
   	printf("\n Arquivo TEXTO.TXT não pode ser aberto : TECLE ALGO");
   	return 0;
   	}

  //Variaveis que estao sendo utilizadas no programa
  char ch; //caracteres percorridos
  int numeroCidade = 0; //numero de cidades da matriz
  char cidades[10][25]; //as cidades presentes no arquivo
  int arestas = 0; //arestas do arquivo
  bool cidade1JaExistente = false; //bool para verificacao de existencia de cidade na matriz
  bool cidade2JaExistente = false; //bool para verificacao de existencia de cidade na matriz
  int matrizDistancia[MAX][MAX]; //matriz contendo as distancias entre cidades
  char cidade1[20], cidade2[20]; //variaveis uteis para preenchimento da matriz de distancias
  int peso, origem, destino, numeroCidade1, numeroCidade2;

  for(int i=0; i<MAX; i++)
    for (int j=0; j<MAX; j++)
        matrizDistancia[i][j] = 0;
  //Salvando o documento em uma matriz para representar as linhas do documento de texto
  while((ch=fgetc(Arquivo))!=EOF) {
    peso = 0;
    if((ch>=0 || ch<=9) && arestas==0) {
      fseek(Arquivo, 0, SEEK_SET);
      fscanf(Arquivo, "%d", &arestas);
      //printf("ARESTAS = %d\n", arestas);
      fseek(Arquivo, 1, SEEK_SET);
    }
    else {
      if(ch>9){
        fscanf(Arquivo, "%s%s%d", cidade1, cidade2, &peso);
        //printf("CIDADE 1 = %s\n", cidade1);
        //printf("CIDADE 2 = %s\n", cidade2);
        //printf("PESO = %d\n", peso);
        if(peso != 0){
          for(int k=0;k<=numeroCidade;k++) {
            //Comparar as strings para saber se a cidade ja existe na matriz de cidades, se a cidade ja existir, ela nao sera acrescentada.
            if((strcmp(cidade1, cidades[k]))==0){
              cidade1JaExistente = true;
              numeroCidade1 = k;
              //printf("NUMERO CIDADE1 = %d\n", numeroCidade1);
            }
            if((strcmp(cidade2, cidades[k]))==0){
              cidade2JaExistente = true;
              numeroCidade2 = k;
              //printf("NUMERO CIDADE1 = %d\n", numeroCidade2);
            }
          }
          if(cidade1JaExistente == false) {
            strcpy(cidades[numeroCidade], cidade1);
            cidade1JaExistente = true;
            numeroCidade1 = numeroCidade;
            numeroCidade++;
            //printf("CIDADES1 = %s\n", cidades[numeroCidade-1]);
            //printf("CIDADE1JAEXISTENTE = %d\n", cidade1JaExistente);
          }
          if(cidade2JaExistente == false) {
            strcpy(cidades[numeroCidade], cidade2);
            cidade2JaExistente = true;
            numeroCidade2 = numeroCidade;
            numeroCidade++;
            //printf("CIDADES2 = %s\n", cidades[numeroCidade-1]);
            //printf("CIDADE2JAEXISTENTE = %d\n", cidade2JaExistente);
          }
          if(cidade1JaExistente == true && cidade2JaExistente == true){
            //printf("ENTREI PRA MONTAR A MATRIZ\n");
            matrizDistancia[numeroCidade1][numeroCidade2]=peso;
            matrizDistancia[numeroCidade2][numeroCidade1]=peso;
          }
          cidade1JaExistente = false;
          cidade2JaExistente = false;
        }
        else {
          for(int k=0;k<=numeroCidade;k++) {
            //Comparar as strings para saber se a cidade ja existe na matriz de cidades, se a cidade ja existir, ela nao sera acrescentada.
            if((strcmp(cidade1, cidades[k]))==0){
              origem = k;
            }
            else if((strcmp(cidade2, cidades[k]))==0){
              destino = k;
            }
          }
        }
      }
    }
  }
  // printf("NUMERO DE CIDADES = %d\n", numeroCidade);
	// printf("Origem = %d\n", origem);
	// printf("Destino = %d\n", destino);
	// for(int i=0; i<numeroCidade; i++){
	// 	printf("\n");
	// 	for (int j=0; j<numeroCidade; j++){
	// 		printf("  %d  ", matrizDistancia[i][j]);
	// 	}
	// }
  // printf("\n");
  //
  // for(int i=0;i<numeroCidade;i++){
  //   printf("CIDADE %d = %s\n", i, cidades[i]);
  // }
  //Fechamento do arquivo
	fclose(Arquivo);
  dijkstra(matrizDistancia, numeroCidade, origem, destino, cidades);
	return 0;
}

int main()
{
  //int i,j,n,u;
  char nomeArquivo[50];
  char limparBuffer;
  printf("Digite o nome do arquivo de entrada: ");
  scanf("%s", nomeArquivo);
  scanf("%c",&limparBuffer);
  gravacaoArquivos(nomeArquivo);
	// printf("Enter no. of vertices:");
	// scanf("%d",&n);
	// printf("\nEnter the adjacency matrix:\n");
  //
	// for(i=0;i<n;i++)
	// 	for(j=0;j<n;j++)
	// 		scanf("%d",&G[i][j]);
  //
	// printf("\nEnter the starting node:");
	// scanf("%d",&u);
	// dijkstra(G,n,u);

	return 0;
}
