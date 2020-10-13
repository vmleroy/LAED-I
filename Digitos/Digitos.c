#include <stdio.h>

int Digitos(int N){
  int digitos = 1;
  //printf("%d\n", n);
  if((N = N/10)>0){
    digitos = digitos + Digitos(N);
    }
  //printf("Digitos: %d\n", digitos);
  return digitos;
}

int main(){
  int N;
  int resultado;
  printf("Digite um numero inteiro: ");
  scanf("%d", &N);
  resultado = Digitos(N);
  printf("Resultado: %d\n", resultado);
}
