#include <stdio.h>

int mdc(int a, int b) {
  //MDC pode ser calculado como a divisao do maior pelo menor e em seguida  o menor divido pelo resto
  //Caso A=0, MDC sera B, caso B=0, MDC sera A
  //Se B=A MDC sera ele mesmo
  if(a==0) {
    return b;
  }
  else if(b==0) {
    return a;
  }
  else {
    if(a>b) {
      return mdc(b, a%b);
    }
    else if (b>a) {
      return mdc(a, b%a);
    }
  }
  return a;
}

int main() {
  int numero1, numero2;
  printf("Digite dois numeros inteiros: ");
  scanf("%d%d", &numero1, &numero2);
  printf("Resultado: %d\n", mdc(numero1, numero2));
}
