/*
Algoritmo de Dijkstra - Caminho Mínimo de Fonte Única

Entrada:
- Número de vértices N
- Matriz de adjacências NxN (0 indica ausência de aresta)
- Vértice origem (source)
- Vértice destino (dest)

Saída:
- Distância mínima de source a dest
- Caminho correspondente ou "Destino inatingivel" se não houver rota

Descrição:
O algoritmo calcula o menor custo do vértice origem a todos os outros,
usando uma abordagem gulosa e uma fila de prioridades simples.
Cada vértice armazena:
  - dist: menor distância conhecida da fonte
  - prev: predecessor no caminho
  - in_queue: flag indicando se ainda está na fila

Etapas principais:
1. Inicializar distâncias (∞ exceto a fonte, que é 0)
2. Repetir até a fila ficar vazia:
   - Extrair o vértice com menor distância (extract_min)
   - Relaxar as arestas que saem dele
3. Imprimir distância e caminho do vértice destino
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1e6

typedef struct Pair{
    int node;
    int soma;
} pair;

typedef struct Lista{
    pair vertice;
    struct Lista* proximo;
} lista;

void show(lista* p){
    if(p == NULL){
        return;
    }
    show(p->proximo);
    printf("%d %d\n", p->vertice.node, p->vertice.soma);
}

lista* push(lista* p, pair v){
    lista* n = malloc(sizeof(lista));
    n->vertice = v;
    n->proximo = p;
    return n;
}

bool empty(lista* p){
    return p == NULL;
}

lista* findMenor(lista* l){
    pair ans;
    ans.soma = INF;
    lista* apontado;
    for(lista* atual = l; atual != NULL; atual = atual->proximo){
        if(atual->vertice.soma < ans.soma){
            ans = atual->vertice;
            apontado = atual;
        }
    }
    return apontado;
}

lista* tira(lista* completa, lista* p){

    if(completa == p){
        lista* nova = completa->proximo;
        free(completa);
        return nova;
    }

    for(lista* atual = completa; atual != NULL; atual = atual->proximo){
        if(atual->proximo == p){
            atual->proximo = p->proximo;
            free(p);
            return completa;
        }
    }
    return completa;
}

void mostra_caminho(int* pai, int fonte, int atual){
    if(atual == fonte){
        printf("Caminho: %d ", fonte);
        return;
    }
    mostra_caminho(pai, fonte, pai[atual]);
    printf("-> %d ", atual);
}

int main(){
    int n;
    scanf("%d", &n);

    int adj[n][n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &adj[i][j]);
        }
    }

    int fonte, destino;
    scanf("%d", &fonte);
    scanf("%d", &destino);

    int dist[n];

    for(int i = 0; i < n; i++){
        dist[i] = INF;
    }

    dist[fonte] = 0;

    lista* l = NULL;

    pair initial = {fonte, 0};

    l = push(l, initial);

    int pai[n];

    while(empty(l) == 0){
        lista* menor = findMenor(l);
        int v = menor->vertice.node;
        int distancia = menor->vertice.soma;
        l = tira(l, menor);

        if(distancia != dist[v]){
            continue;
        }

        for(int i = 0; i < n; i++){
            if(adj[v][i] > 0){
                    if(distancia + adj[v][i] < dist[i]){
                    dist[i] = distancia + adj[v][i];
                    pai[i] = v;
                    pair temp = {i, dist[i]};
                    l = push(l, temp);
                }
            }
        }
    }
    
    if(dist[destino] == INF){
        printf("Destino inatingivel\n");
        return 0;
    }
    
    printf("Distancia minima de %d para %d: %d\n", fonte, destino, dist[destino]);
    mostra_caminho(pai, fonte, destino);

}
