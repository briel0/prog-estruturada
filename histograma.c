/*
 * Histograma
 *
 * Um histograma é uma representação da distribuição de frequências
 * de um conjunto de dados numéricos. Ele divide o eixo dos valores
 * em intervalos contíguos e não sobrepostos (bins) e conta quantos
 * elementos caem em cada intervalo.
 *
 * Programa:
 * 1. Ler duas dimensões m e n.
 * 2. Ler m linhas com n valores double por linha (linha a linha).
 * 3. Calcular o histograma dos m*n valores.
 * 4. Imprimir o histograma no formato:
 *       centro_do_bin: sequência_de_asteriscos
 * 5. Implementar:
 *    - função histograma que calcula as frequências dos bins.
 *    - função imprimir que mostra o histograma na tela.
 *    - garantir que toda memória alocada dinamicamente seja desalocada.
 *
 * Método para determinar os bins (Regra de Rice):
 *  - Número de bins B = ceil(2 * N^(1/3)), onde N = m*n.
 *  - Largura do bin: w = (xmax - xmin) / B, onde xmin e xmax são os extremos dos dados.
 *  - Centro do bin i (i = 0, 1, ..., B-1): ci = xmin + (i + 0.5) * w
 *  - Atribuição de cada valor x a um bin:
 *       i(x) = floor((x - xmin) / w)
 *       Para garantir que o valor máximo caia no último bin:
 *       i(x) = min(max(floor((x - xmin)/w), 0), B-1)
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int m, n;
    int i, j, N, B;
    double xmin, xmax, w;

    scanf("%d %d", &m, &n);
    N = m * n;

    double* valores = malloc(sizeof(double) * N);

    for(i = 0; i < N; i++){
        scanf("%lf", &valores[i]);
    }

    xmin = xmax = valores[0];
    for(i = 1; i < N; i++){
        if(valores[i] < xmin){
            xmin = valores[i];
        }
        if(valores[i] > xmax){
            xmax = valores[i];
        }
    }

    B = (int)ceil(2 * pow(N, 1.0 / 3.0));

    w = (xmax - xmin) / B;

    int contagem[B];
    for(i = 0; i < B; i++){
        contagem[i] = 0;
    }

    for(i = 0; i < N; i++){
        int idx = (int)floor((valores[i] - xmin) / w);
        if(idx < 0){
            idx = 0;
        }
        if(idx >= B){
            idx = B - 1;
        }
        contagem[idx]++;
    }

    for(i = 0; i < B; i++){
        double centro = xmin + (i + 0.5) * w;
        printf("%6.2f: ", centro);
        for(j = 0; j < contagem[i]; j++){
            printf("*");
        }
        printf("\n");
    }

    free(valores);

    return 0;
}
