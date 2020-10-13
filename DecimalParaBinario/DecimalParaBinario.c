#include <stdio.h>

void dec2bin(int dec) {
  int resto,quociente;
    if(dec > 0) {
      quociente = dec/2;
      resto = (dec%2);
      dec2bin(quociente);
      //printf("%d/2 = %d resto %d\n", dec, quociente, resto);
      printf("%d", resto);
    }
}

int main() {
  int numero;
  printf("Digite um numero inteiro: ");
  scanf("%d", &numero);
  printf("Resultado: ");
  if(numero != 0)
    dec2bin(numero);
  else
    printf("0");
  printf("\n");
}
