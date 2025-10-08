/*
ENUNCIADO:
Um número Harshad (também conhecido como Número de Niven) é um número inteiro que é divisível pela soma de seus próprios dígitos. Por exemplo, o número 21 é um número Harshad porque a soma de seus dígitos é  (2 + 1 = 3), 
e 21 é divisível por 3 (21 / 3 = 7). Outro exemplo é 156: a soma dos dígitos é (1 + 5 + 6 = 12), e 156 é divisível por 12 (156 / 12 = 13). 
Crie programa que implemente uma função em C chamada ehHarshad que receba um número inteiro como entrada e retorne 1 (verdadeiro) se o número for um Harshad, ou 0 (falso) caso contrário. 
*/

#include <stdio.h>

int ehHarshad(int n){
    int soma = 0, copia = n;
    while(n){
        soma += n % 10;
        n /= 10;
    }
    return (copia % soma) == 0;
}

int main(){

    int n;
    scanf("%d", &n);
    if(ehHarshad(n)){
        printf("%d", 1);
    }
    else{
        printf("%d", 0);
    }

    return 0;
}
