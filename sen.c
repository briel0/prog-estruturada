/*
ENUNCIADO:
A série de Taylor é uma representação de uma função como uma soma infinita de termos, calculados a partir dos valores das derivadas da função em um único ponto.
Escreva um programa que implemente a função em C chamada calcularSenoTaylor que receba um ângulo x (em radianos) e um número num_termos como entrada. A função deve calcular e retornar uma aproximação de 
sen(x) usando a série de Taylor, somando num_termos da série.
*/

#include <stdio.h>

double calcularSenoTaylor(double x, int termos){
    double atual = x, soma = x;

    for(int i = 0; i < termos - 1; i++){
        double novo = atual * -1;
        novo *= x * x;
        novo /= ((2 * i + 2) * (2 * i + 3));
        soma += novo;
        atual = novo;
    }
    return soma;
}

int main(){

    double x;
    int termos;
    scanf("%lf", &x);
    scanf("%d", &termos);

    double ans = calcularSenoTaylor(x, termos);

    printf("sen(%.8lf) = %.8lf", x, ans);

    return 0;
}
