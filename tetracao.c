/*
ENUNCIADO:
A tetração é a próxima operação na hierarquia das hiperoperações,
após a adição, multiplicação e exponenciação. Enquanto a exponenciação
(x^n) é a repetição da multiplicação (x * x * ... * x, n vezes), a 
tetracão é a repetição da exponenciação. 

A notação comum para tetração é n↑↑x (lê-se "n tetrado a x"). A operação é definida como:

n↑↑x = x^(x^(...^x))  // 'x' aparece n vezes

É importante notar que a "torre exponencial" é avaliada de cima para baixo. 
Por exemplo:

3↑↑2 = 2^(2) = 2^2 = 4

4↑↑2 = 2^(2^2) = 2^4 = 16

4↑↑3 = 2^(2^(2^2)) = 2^(2^4) = 2^16 = 65536

Escreva um programa que implemente a função recursiva em C, chamada 
tetracao, que calcule n↑↑x para valores reais x (positivos) e inteiros 
não negativos n.
*/

#include <stdio.h>
#include <math.h>

long double tetra(long double x, int n){
    if(n == 0){
        return 1;
    }
    return pow(x, tetra(x, n - 1));
}

int main(){
    long double x;
    int n;
    scanf("%Lf", &x);
    scanf("%d", &n);
    printf("^%d(%.8Lg) = %.8Lg\n", n, x, tetra(x, n));
}
