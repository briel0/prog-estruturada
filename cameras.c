/*
Otimizacao de Cameras de Seguranca

Joaozinho possui uma empresa especializada em seguranca de condominios
e precisa otimizar a colocacao de cameras para cobrir todas as ruas,
usando exatamente K cameras.

Modelo do Condominio:
- Cada rua conecta exatamente duas esquinas.
- Nao existem becos ou ruas sem saida.
- Uma camera tem visao 360 graus e cobre todas as ruas que tocam
  a esquina onde ela esta instalada.
- As cameras so podem ser instaladas nas esquinas.

Objetivo:
Encontrar um conjunto de esquinas onde as cameras devem ser colocadas
para cobrir todas as ruas usando exatamente K cameras.

Entrada:
- A primeira linha contem tres inteiros N, M e K.
  N: numero de esquinas (0 a N-1)
  M: numero de ruas
  K: numero exato de cameras
- As N linhas seguintes representam a matriz de adjacencia (N x M)
  com valores 0 ou 1 separados por espacos.
  A[i][j] = 1 se a esquina i e extremidade da rua j,
  A[i][j] = 0 caso contrario.
  Cada coluna (rua) tem exatamente dois valores iguais a 1.

Restricoes:
3 <= N <= 30
3 <= M <= 50
1 <= K <= N

Saida:
- Se nao for possivel cobrir todas as ruas com K cameras, imprimir -1.
- Caso contrario, imprimir os identificadores das K esquinas
  em ordem crescente, separados por espacos, seguidos de quebra de linha.

Criterio de desempate:
Se existirem multiplas combinacoes validas,
imprimir a combinacao lexicograficamente menor.
Exemplo:
{0, 1, 3, 5, 7, 9} e {1, 2, 3, 5, 7, 9}
=> Saida esperada: 0 1 3 5 7 9
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct lista{
    int value;
    struct lista* anterior;
} Lista;

Lista* coloca(Lista* atual, int novo){
    Lista* temp = malloc(sizeof(Lista));
    temp->value = novo;
    temp->anterior = atual;
    return temp;
}

Lista* tira(Lista* atual){
    Lista* anterior = atual->anterior;
    free(atual);
    return anterior;
}

void mostra(Lista* atual){
    if(atual == NULL){
        return;
    }
    mostra(atual->anterior);
    printf("%d ", atual->value);
}

Lista* pilha = NULL;

int n, m;

#define N 30
#define M 50
int adj[N + 1][N + 1];
int vigiada[M + 1];

bool achou;

void distribuiCameras(int atual, int cameras){
    //verifica a solução
    
    if(achou){
        return;
        //pra podar a árvore de recursão paramos a busca depois de achar alguma resposta
        //como exploramos as esquinas em ordem crescente a primeira resposta encontrada
        //sempre vai ser a lexicograficamente menor
    }

    if(atual == n || cameras == 0){
        bool invalida = 0;
        for(int i = 1; i <= m; i++){
            invalida |= (vigiada[i] == 0);
        }   

        if(!invalida && !achou){
            mostra(pilha);
            achou = 1;
        }
        return;
    }

    pilha = coloca(pilha, atual);

    for(int i = 0; i < n; i++){
        vigiada[adj[atual][i]]++;
    }

    distribuiCameras(atual + 1, cameras - 1);

    pilha = tira(pilha);

    for(int i = 0; i < n; i++){
        vigiada[adj[atual][i]]--;
    }

    distribuiCameras(atual + 1, cameras);

}

int main(){
    int k;
    scanf("%d %d %d", &n, &m, &k);

    int original[n][m];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &original[i][j]);
        }
    }

    for(int j = 0; j < m; j++){
        int a = -1;
        for(int i = 0; i < n; i++){
            if(original[i][j] == 1){
                if(a == -1){
                    a = i;
                }
                else{
                    adj[a][i] = j + 1;
                    adj[i][a] = j + 1;
                }
            }
        }
    }

    distribuiCameras(0, k); //começa na esquina 0
    if(!achou){
        printf("-1");
    }
}
