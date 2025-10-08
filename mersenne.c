/*
ENUNCIADO:
Um número primo de Mersenne é um número primo da forma M_i = 2^i - 1, 
onde i também deve ser um número primo. Nem todos os números da forma 
2^i - 1 são primos, mesmo que i seja primo. Por exemplo, 2^11 - 1 = 2047, 
que não é primo (2047 = 23 * 89). 

Os primeiros primos de Mersenne são:
M_2 = 3, M_3 = 7, M_5 = 31, M_7 = 127, M_13 = 8191, etc.

Escreva um programa que implemente a função em C chamada
encontrarPrimosMersenne que receba um número inteiro n como entrada
e imprima todos os números primos de Mersenne que são menores que n.
*/

#include <stdio.h>
#include <stdbool.h>

bool primo(int n){
    if(n <= 1){
        return false;
    }
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

void encontrarPrimosMersenne(int n){
    if(n < 4){
        printf("Nenhum primo de Mersenne encontrado.\n");
        return;
    }
    printf("Os primos de Mersenne menores que %d sao: ", n);
    int cnt = 0;
    int atual = 1;
    while(atual < n){
        if(primo(atual - 1)){
            printf("%d", atual - 1);
            if((atual << 1) >= n){
                printf(".\n");
            }
            else{
                printf(", ");
            }
        }
        atual <<= 1;
    }
}

int main(){
    int n;
    scanf("%d", &n);

    encontrarPrimosMersenne(n);

}
