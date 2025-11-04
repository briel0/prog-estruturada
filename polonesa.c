/*
Avaliação de Expressões Aritméticas Pós-fixas (Notação Polonesa Inversa)

Objetivo:
Ler uma expressão pós-fixa e calcular seu valor numérico usando uma pilha (TAD Stack).

Descrição:
- Na notação pós-fixa, operadores vêm após os operandos (ex: "3 4 +").
- Isso elimina parênteses e facilita a avaliação com pilha.

Algoritmo:
1. Ler a expressão completa com fgets().
2. Quebrar a expressão em tokens usando strtok().
3. Para cada token:
   - Se for número → converter com atof() e empilhar.
   - Se for operador → desempilhar dois operandos, aplicar a operação e empilhar o resultado.
4. Ao final, o valor no topo da pilha é o resultado final.
5. Imprimir o resultado com duas casas decimais.

Operadores suportados: +, -, *, /
Operandos: inteiros ou floats
Exemplo:
Entrada:  2 3 + 5 *
Saída:    25.00
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef struct pilha{
    double value;
    struct pilha* prox;
} Pilha;

Pilha* push(Pilha* p, double x){
    Pilha* novo = malloc(sizeof(Pilha));
    novo->value = x;
    novo->prox = p;
    return novo;
}

Pilha* pop(Pilha* p){
    Pilha* temp = p->prox;
    free(p);
    return temp;
}

void libera(Pilha* p){
    if(p == NULL){
        return;
    }
    libera(p->prox);
    free(p);
}

double opera(double um, double dois, char* operador){
    if(!strcmp(operador, "+")){
        return um + dois;
    }
    if(!strcmp(operador, "-")){
        return um - dois;
    }
    if(!strcmp(operador, "/")){
        return um / dois;
    }
    if(!strcmp(operador, "*")){
        return um * dois;
    }
    return 0;
}

int main(){
    char temp;
    
    char* atual = malloc(1);

    atual[0] = '\0';

    int len = 0;

    bool ultimoNum = 0;

    Pilha* p = NULL;

    while(scanf("%c", &temp) == 1){
        if(temp == ' ' || temp == '\n'){

            if(ultimoNum){
                double x = atof(atual);
                p = push(p, x);
            }
            else{
                double dois = p->value;
                p = pop(p);
                double um = p->value;
                p = pop(p);
                double result = opera(um, dois, atual);
                p = push(p, result);
            }

            free(atual);
            atual = malloc(1);
            atual[0] = '\0';
            len = 0;
        }
        else{
            atual = realloc(atual, len + 2);
            atual[len] = temp;
            atual[++len] = '\0';
            ultimoNum = isdigit(temp);
        }
    }
    double ans = p->value;
    printf("Resultado da avaliacao: %.2f\n", ans);
    free(atual);
    libera(p);
}
