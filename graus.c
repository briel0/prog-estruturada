/*
Objetivo:
Implementar um programa em C que, dada uma rede social representada como um grafo,
calcule o menor número de conexões (grau de separação) entre duas pessoas e mostre
o caminho entre elas.

Descrição:
- Cada pessoa é um vértice do grafo.
- Cada amizade é uma aresta (conexão bidirecional).
- A estrutura usada será uma lista de adjacências.
- O cálculo do menor caminho será feito com o algoritmo BFS (Busca em Largura).

Entrada:
1. Capacidade inicial do grafo.
2. Número de conexões.
3. Pares de nomes representando amizades.
4. Dois nomes para a consulta do grau de separação.

Saída:
- Grau de separação entre as duas pessoas.
- Caminho percorrido entre elas (ou mensagem se não houver caminho).
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Lista{
    char* value;
    struct Lista* proximo;
} lista;

typedef struct Node{
    char* nome;
    lista* adj;
} node;

char* ler_string(){
    char* str = NULL;
    char c;
    int len = 0;
    while((c = getchar()) != EOF && c != '\n' && c != ' '){
        str = realloc(str, (len + 1) * sizeof(char));
        str[len++] = c;
    }
    str = realloc(str, (len + 1) * sizeof(char));
    str[len] = '\0';
    return str;
}

lista* insert(lista* completa, char* atual){
    lista* novo = malloc(sizeof(lista));
    novo->value = atual;
    novo->proximo = completa;
    return novo;
}

void show_lista(lista* completa){
    if(completa == NULL){
        return;
    }
    printf("%s\n", completa->value);
    show_lista(completa->proximo);
}

typedef struct Fila{
    lista* inicio;
    lista* fim;
} fila;

fila* push(fila* completa, char* atual){
    lista* novo = malloc(sizeof(lista));
    novo->value = atual;
    novo->proximo = NULL;

    if(completa->fim == NULL){
        completa->inicio = novo;
    }
    else{
        completa->fim->proximo = novo;
    }
    completa->fim = novo;
    return completa;
}

int get_number(node* control, int n, char* atual){
    for(int i = 0; i < n; i++){
        if(strcmp(control[i].nome, atual) == 0){
            return i;
        }
    }
}

bool empty(fila* p){
    return p->fim == NULL;
}

fila* pop(fila* p){
    lista* temp = p->inicio;
    if(p->inicio == p->fim){
        p->fim = NULL;
    }
    p->inicio = temp->proximo;
    free(temp);
    return p;
}

void show_path(node* control, int n, int* pai, int init, int destino, int atual){
    if(atual == init){
        printf("%s -> ", control[atual].nome);
        return;
    }
    show_path(control, n, pai, init, destino, pai[atual]);
    printf("%s", control[atual].nome);
    if(atual != destino){
        printf(" -> ");
    }
}

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    getchar();

    node control[n + 1];

    for(int i = 0; i < n; i++){
        control[i].nome = NULL;
        control[i].adj = NULL;
    }

    int ultimo = 0;

    while(m--){
        char* um = ler_string();
        char* dois = ler_string();
        
        bool temu = 0, temd = 0;
        for(int i = 0; i < n; i++){
            temu |= control[i].nome && (strcmp(control[i].nome, um) == 0);
            temd |= control[i].nome && (strcmp(control[i].nome, dois) == 0);
        }
        if(!temu){
            control[ultimo].nome = um;
            ultimo++;
        }
        
        if(!temd){
            control[ultimo].nome = dois;
            ultimo++;
        }
        for(int i = 0; i < n; i++){
            if(control[i].nome && strcmp(control[i].nome, um) == 0){
                control[i].adj = insert(control[i].adj, dois);
            }
            if(control[i].nome && strcmp(control[i].nome, dois) == 0){
                control[i].adj = insert(control[i].adj, um);
            }
        }
    }

    char* um = ler_string();
    char* dois = ler_string();

    int init = -1;

    for(int i = 0; i < n; i++){
        if(strcmp(control[i].nome, um) == 0){
            init = i;
            break;
        }
    }

    fila* p = malloc(sizeof(fila));
    p->inicio = NULL;
    p->fim = NULL;

    p = push(p, control[init].nome);

    int visited[n + 1], pai[n + 1];

    for(int i = 0; i < n; i++){
        visited[i] = 0;
        pai[i] = -1;
    }

    visited[init] = 1;

    while(!empty(p)){
        char* atual = p->inicio->value;
        p = pop(p);
        int v = get_number(control, n, atual);

        for(lista* i = control[v].adj; i != NULL; i = i->proximo){
            int viva = get_number(control, n, i->value);
            if(!visited[viva]){
                visited[viva] = visited[v] + 1;
                p = push(p, i->value);
                pai[viva] = v;
            }
        }
    }
    
    int destino = get_number(control, n, dois);

    if(!visited[destino]){
        printf("Nao ha caminho de %s para %s\n", um, dois);
        return 0;
    }
    
    printf("Grau de separacao entre %s e %s: %d\n", um, dois, visited[destino] - 1);
    printf("Caminho: ");
    show_path(control, n, pai, init, destino, destino);

    free(p);
    free(um);
    free(dois);

    for(int i = 0; i < n; i++){
        free(control[i].nome);
        lista* atual = control[i].adj;
        while(atual != NULL){
            lista* temp = atual->proximo;
            free(atual);
            atual = temp;
        }
    }

}
