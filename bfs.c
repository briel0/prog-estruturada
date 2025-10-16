/*
O exercício pedia uma implementação de BFS em C
*/

#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INFINITO 999999

typedef struct Node{
    int value;
    struct Node* prox;
} Node;

typedef struct Fila{
    Node* frente;
    Node* tras;
} Fila;

Fila* criaFila(){
    Fila* f = malloc(sizeof(Fila));
    f->frente = f->tras = NULL;
    return f;
}

void push(Fila* f, int valor){
    Node* novo = malloc(sizeof(Node));
    novo->value = valor;
    novo->prox = NULL;

    if(f->tras == NULL){
        f->frente = f->tras = novo;
        return;
    }

    f->tras->prox = novo;
    f->tras = novo;
}

void pop(Fila* f){
    Node* temp = f->frente;
    int valor = temp->value;

    f->frente = f->frente->prox;

    free(temp);

    if(f->frente == NULL){
        f->tras = NULL;
    }
}

int empty(Fila* f){
    return f->frente == NULL;
}

void bfs(int** adj, int n, int fonte){
    
    int cores[n + 1];
    int distancias[n + 1];
    int predecessores[n + 1];

    for(int i = 0; i < n; i++){
        distancias[i] = INFINITO;
        predecessores[i] = -1;
        cores[i] = BRANCO;
    }

    Fila* f = criaFila();

    cores[0] = CINZA;
    distancias[0] = 0;
    push(f, 0);

    while(!empty(f)){
        int v = f->frente->value;
        pop(f);

        for(int i = 0; i < n; i++){
            if(adj[i][v] == 1){
                if(cores[i] == BRANCO){
                    cores[i] = CINZA;
                    distancias[i] = distancias[v] + 1;
                    predecessores[i] = v;
                    push(f, i);
                }
            }
        }
        cores[v] = PRETO;
    }

    printf("BFS a partir do vértice 0:\n");

    for(int i = 0; i < n; i++){
        printf("Vertice %d: Distancia: %d, Predecessor = %d\n", i, distancias[i], predecessores[i]);
    }

}

int main(){
    int n;
    scanf("%d", &n);

    int** grafo = malloc((n + 1) * sizeof(int*));
    for(int i = 0; i < n; i++){
        grafo[i] = malloc((n + 1) * sizeof(int));
        for(int j = 0; j < n; j++){
            scanf("%d", &grafo[i][j]);
        }
    }

    bfs(grafo, n, 0);

    for(int i = 0; i < n; i++){
        free(grafo[i]);
    }
    free(grafo);
}
