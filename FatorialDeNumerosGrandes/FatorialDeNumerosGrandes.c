#include <stdio.h>
#include <stdlib.h>

void printarResultado(int *vetorResultado, int tamanho) {
  int i;
  for(i=tamanho-1;i>=0;i--) {
    printf("%d", vetorResultado[i]);
  }
  printf("\n");
}

void fatorial(int *vetorResultado, int numero) {
  int i,tamanho = 1,j=0,carryOut=0,resultado;
  if(numero<0) {
    printf("Nao pode ser realizado fatorial de numero negativo\n");
  }
  else if((numero==1) || (numero == 0)){
    printf("Resultado: 1\n");
  }
  else {
    for(i=1;i<=numero;i++) {

      while(j<tamanho) {
          resultado = vetorResultado[j]*i + carryOut;
          carryOut = resultado/10;
          vetorResultado[j] = resultado%10;
          j++;
          // printf("J = %d\n", j);
          // printf("VETORRESULTADO = %d\n", vetorResultado[j]);
          // printf("carryOut = %d\n", carryOut);
        }
      while(carryOut!=0) {
          vetorResultado[j] = carryOut%10;
          carryOut = carryOut/10;
          j++;
        }
      j-=tamanho;
      tamanho+=j;
      j=0;
    }
    //printf("TAMANHO = %d\n", tamanho);
    printf("Resultado: ");
    printarResultado(vetorResultado,tamanho);
  }
}

int main() {
  int numero, *vetorResultado;
  //printf("~$\n");
  printf("Digite um numero inteiro: ");
  scanf("%d", &numero);
  vetorResultado = calloc(100000, sizeof(int));
  vetorResultado[0] = 1;
  // printf("VETORRESULTADO = %d\n", vetorResultado[0]);
  fatorial(vetorResultado, numero);
  //printf("~$\n");
}
