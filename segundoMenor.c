/*
Implemente uma função em C que receba um vetor de inteiros com tamanho fixo de 10 posições e determine o segundo menor valor distinto presente nesse vetor. Considere que o vetor contém pelo menos dois valores diferentes.
*/

#include <stdio.h>

int segundoMenorValor(const int v[]){
    int menor = v[0];
    for(int i = 1; i < 10; i++){
        if(v[i] < menor){
            menor = v[i];
        }
    }

    int outro;

    for(int i = 0; i < 10; i++){
        if(v[i] != menor){
            outro = v[i];
            break;
        }
    }

    for(int i = 0; i < 10; i++){
        if(v[i] == menor){
            continue;
        }
        if(v[i] < outro){
            outro = v[i];
        }
    }
    return outro;
}

int main(){
    int v[10] = {};
    printf("Vetor: ");
    for(int i = 0; i < 10; i++){
        scanf("%d", &v[i]);
        printf("%d ", v[i]);
    }
    printf("\n");
    printf("Segundo menor valor: %d\n", segundoMenorValor(v));

}
