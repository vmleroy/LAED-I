#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 2

//testes+
//#bwf#ho#urruly
//rglfil#drwF#w#udvdgrsdhvkqdi#hpohxhwrpfhp#dudgilvhg#t#qhv#lfhw#u#d#hqhs#r#vhahhgf#uidu#D
//VR#RLOUYPD
//#QDWDEI##RDWHXPRT#F#MLLU#HDWRFDE

int tamanhoTrechoF(char *trechoCodificado) {
	int i=0;
 	while(trechoCodificado[i]!='\0') {
 		i++;
 	}
 	return i;
}

int leituraArquivo (char nomeArquivo[], char *trechoCodificado) {
	FILE *Arquivo;
	Arquivo = fopen(nomeArquivo,"r");
	if (Arquivo == NULL) {
 	printf("\n Arquivo TEXTO.TXT não pode ser aberto : TECLE ALGO");
 	return 0;
 	}
 	fscanf(Arquivo, "%s", trechoCodificado);
 	//printf("%s\n", trechoCodificado);
 	fclose(Arquivo);
 	return 1;
}

void subdivisaoTrechoCodificado(char *trechoCodificado, int tamanhoTrecho) {
	char aux, aux2;
	int letras=0;
	for(int i=0;i<(tamanhoTrecho/2);i+=2){
		if(letras%2==0) {
			aux = trechoCodificado[i];
			aux2 = trechoCodificado[i+1];
			trechoCodificado[i] = trechoCodificado[tamanhoTrecho - i - 2];
			trechoCodificado[i+1] = trechoCodificado[tamanhoTrecho - i - 1];
			trechoCodificado[tamanhoTrecho - i - 2] = aux;
			trechoCodificado[tamanhoTrecho - i - 1] = aux2;
			// printf("AUX  = %c\n", aux);
			// printf("AUX2 = %c\n", aux2);
			// printf("trechoCodificado = %c\n", trechoCodificado[i]);
			// printf("trechoCodificado = %c\n", trechoCodificado[i+1]);
		}
		letras++;
	}
	//printf("SUBDIVISAO DE TRECHOS = %s\n", trechoCodificado);
	//printf("\n");
}

void permutacaoTrechoCodificado(char *trechoCodificado, int tamanhoTrecho) {
	int letras=1;
	char aux,aux2;
	//printf("%s\n", trechoCodificado);
	for(int i=0;i<tamanhoTrecho;i++) {
		letras++; 
		if(letras==n) {
			aux = trechoCodificado[i];
			aux2 = trechoCodificado[i+1];
			trechoCodificado[i]  = aux2;
			trechoCodificado[i+1] = aux;
			// printf("AUX  = %c\n", aux);
			// printf("AUX2 = %c\n", aux2);
			letras=0;
		}
		//printf("LETRAS = %d\n", letras);
	}
	//printf("PERMUTACAO = %s\n", trechoCodificado);
	//printf("\n");
}

void decifrarCodigo(char *trechoCodificado, int tamanhoTrecho) {
	int i;
	for(i=0;i<tamanhoTrecho;i++) {
		if(trechoCodificado[i]=='#') {
			trechoCodificado[i] = ' ';
		}
		else{
			switch(trechoCodificado[i]) {
				case 67:
					trechoCodificado[i] = 90;
					break;
				case 99:
					trechoCodificado[i] = 122;
					break;
				case 66:
					trechoCodificado[i] = 89;
					break;
				case 98:
					trechoCodificado[i] = 121;
					break;
				case 65:
					trechoCodificado[i] = 88;
					break;
				case 97:
					trechoCodificado[i] = 120;
					break;
				default:
					trechoCodificado[i]-=3;
					break;
			}
		}
	}
	trechoCodificado[i] = '\0';
	//printf("%s\n", trechoCodificado);
}

void printarResposta(char *trechoCodificado, char *trechoCodificadoAux) {
	printf("\n--------------------\n");
    printf("Mensagem codificada:");
	printf("\n--------------------\n");
	printf("%s\n", trechoCodificadoAux);
	printf("\n----------------------\n");
    printf("Mensagem decodificada:");
	printf("\n----------------------\n");
	printf("%s\n", trechoCodificado);
}

int main() {
	char nomeArquivo[50];
	char *trechoCodificado, *trechoCodificadoAux;
	int tamanhoTrecho;
	
	printf("Digite o nome do arquivo: ");
	scanf("%s", nomeArquivo);
	//printf("\n");

	trechoCodificado = malloc (10000*sizeof(char));
	trechoCodificadoAux = malloc (10000*sizeof(char));
	leituraArquivo(nomeArquivo, trechoCodificado);
	strcpy(trechoCodificadoAux, trechoCodificado);
	tamanhoTrecho = tamanhoTrechoF(trechoCodificado);
	//printf("%ld\n", strlen(trechoCodificado));
	//printf("TAMANHO = %d\n", tamanhoTrecho);
	
	//trocarEspacos(trechoCodificado, tamanhoTrecho, trechoCodificadoAux);
	subdivisaoTrechoCodificado(trechoCodificado, tamanhoTrecho);
	permutacaoTrechoCodificado(trechoCodificado, tamanhoTrecho);
	decifrarCodigo(trechoCodificado, tamanhoTrecho);
	printarResposta(trechoCodificado, trechoCodificadoAux);
}	