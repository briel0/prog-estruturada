/* 
Simulação de distribuição de candidatos em um vestibular com lista encadeada.

- Cada candidato tem: chave, nota final e 3 opções de curso.
- Os cursos (1 a 7) possuem número limitado de vagas.
- Os candidatos são armazenados em uma lista encadeada ordenada por:
    1. NotaFinal (decrescente)
    2. Chave (crescente, como desempate)
- Inserções mantêm a lista sempre ordenada.

Etapas do programa:
1. Ler número de vagas de cada curso.
2. Ler dados dos candidatos (até chave = 0) e inserir ordenadamente na lista.
3. Percorrer a lista e tentar alocar cada candidato nas suas opções de curso.
   - Aloca na primeira opção com vaga disponível.
   - Se não conseguir em nenhuma, é considerado reprovado.
4. Exibir resultados:
   - Candidatos aprovados por curso (ou “Nenhum” se vazio)
   - Lista de reprovados.
5. Liberar toda memória alocada dinamicamente.

Vantagens da lista encadeada:
- Inserção eficiente e ordenada sem deslocar elementos.
- Uso dinâmico de memória (sem desperdício).
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Candidato{
    int chave;
    int nota;
    int options[3];
} candidato;

typedef struct Lista{
    candidato esse;
    struct Lista* proximo;
} lista;

void show_candidato(candidato atual){
    printf("chave-> %d\n", atual.chave);
    printf("nota-> %d\n", atual.nota);
    for(int i = 0; i < 3; i++){
        printf("opcao %d -> %d\n", i, atual.options[i]);
    }
}

lista* insert(lista* completa, lista* atual){
    if(completa == NULL){
        atual->proximo = completa;
        return atual;
    }

    for(lista* i = completa; i != NULL; i = i->proximo){
        lista* prox = i->proximo;
        if(prox == NULL){
            i->proximo = atual;
            atual->proximo = prox;
            return completa;
        }
        else{
            if(prox->esse.nota < atual->esse.nota || 
            (prox->esse.nota == atual->esse.nota && prox->esse.chave > atual->esse.chave)){
                i->proximo = atual;
                atual->proximo = prox;
                return completa;
            }
        }
    }

}

void show_lista(lista* atual){
    if(atual == NULL){
        return;
    }
    show_candidato(atual->esse);
    show_lista(atual->proximo);
}

int main(){

    int vagas[7] = {};

    for(int i = 0; i < 7; i++){
        scanf("%d", &vagas[i]);
    }

    lista* l = NULL;

    int chave, nota;
    int op[3];
    while(scanf("%d %d %d %d %d", &chave, &nota, &op[0], &op[1], &op[2]) && chave){ 
        candidato novo;
        novo.chave = chave;
        novo.nota = nota;
        for(int i = 0; i < 3; i++){
            op[i]--;
            novo.options[i] = op[i];
        }

        lista* lnovo = malloc(sizeof(lista));

        lnovo->esse = novo;

        l = insert(l, lnovo);

    }

    show_lista(l);

    lista* aprovados[7];
    lista* reprovados = NULL;

    for(int i = 0; i < 7; i++){
        aprovados[i] = NULL;
    }

    for(lista* atual = l; atual != NULL; atual = atual->proximo){
        candidato aluno = atual->esse;
        bool aprovado = 0;
        for(int i = 0; i < 3; i++){
            if(vagas[aluno.options[i]]){
                lista* temp = malloc(sizeof(lista));
                temp->esse = aluno;
                aprovados[aluno.options[i]] = insert(aprovados[aluno.options[i]], temp);
                aprovado = 1;
                vagas[aluno.options[i]]--;
                break;
            }
        }
        if(!aprovado){
            lista* temp = malloc(sizeof(lista));
            temp->esse = aluno;
            reprovados = insert(reprovados, temp);
        }
    }

    for(int i = 0; i < 7; i++){
        printf("Aprovados Curso %d: ", i + 1);
        if(aprovados[i] == NULL){
            printf("Nenhum\n");
            continue;
        }
        for(lista* atual = aprovados[i]; atual != NULL; atual = atual->proximo){
            printf("%d", atual->esse.chave);
            if(atual->proximo != NULL){
                printf(", ");
            }
        }
        printf("\n");
    }

    printf("Reprovados: ");
    if(reprovados == NULL){
        printf("Nenhum\n");
        return 0;
    }


    for(lista* atual = reprovados; atual != NULL; atual = atual->proximo){
        printf("%d", atual->esse.chave);
        if(atual->proximo != NULL){
            printf(", ");
        }
    }
    printf("\n");

}
