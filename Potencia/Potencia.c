#include <stdio.h>

int mult(int base, int exp) {
  //Se o expoente = 0, return 1
  if(exp == 0) {
    return 1;
  }
  else {
    //Nesse caso precisamos de multiplicar a base por ela mesmo enquanto o expoente for > 0 para termos
    return (base * mult(base, (exp-1)));
  }
  return 0;
}

int main() {
  int base, exp;
  printf("Digite a base e o expoente inteiros: ");
  scanf("%d%d", &base, &exp);
  printf("Resultado: %d\n", mult(base, exp));
}
