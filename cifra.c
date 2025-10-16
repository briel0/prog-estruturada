/*
    Cifra Monoalfabética

    Uma cifra monoalfabética é um método de criptografia por substituição em que 
    cada letra do alfabeto do texto claro é sempre mapeada para a mesma letra do alfabeto cifrado,
    usando uma chave fixa (uma permutação das 26 letras).

    Regras:
    - Cada letra de 'a' a 'z' do texto é substituída por outra letra de 'a' a 'z' definida pela chave.
    - Todo 'a' vira sempre a mesma letra, todo 'b' vira sempre a mesma letra, etc.
    - Não é segura para uso moderno, pois pode ser quebrada por análise de frequência.

    Simplificações:
    - O texto contém apenas letras minúsculas a-z, espaços e pontuação.
    - Não há cedilha (ç) nem caracteres acentuados.
    - A chave tem exatamente 26 caracteres, todos a-z, sem repetição.
    - Comprimento máximo do texto: 200 caracteres.

    Entradas do programa:
    1. Uma opção de função: 'E' para encriptação ou 'D' para decriptação.
    2. Uma string de até 200 caracteres (texto ou cifra).
    3. Uma chave de 26 caracteres (permutação do alfabeto a-z).

    Saída do programa:
    - O texto resultante após aplicar a função escolhida:
        E(texto claro, chave) → texto encriptado
        D(texto cifrado, chave) → texto decriptado

    Assinaturas das funções:
    - char* encripta(char *texto, char *chave);
    - char* decripta(char *cifra, char *chave);

    Dicas:
    - Detectar letras com <ctype.h>: isalpha((unsigned char)c)
    - Apenas letras 'a'..'z' são substituídas; outros caracteres (espaço/pontuação) são copiados diretamente.
    - Se usar fgets após scanf, inserir um getchar:
        scanf("%c", &modo);
        getchar();
        fgets(texto, sizeof(texto), stdin);

    Exemplo de chave:
    zyxwvutsrqponmlkjihgfedcba
    (a→z, b→y, ..., z→a)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void copia(char* texto, char* chave){
    int tamanho = strlen(texto) + 1;

    char* copia = malloc(tamanho);

    strcpy(copia, texto);

    printf("%s\n", copia);

}

char* encripta(char* texto, char* chave){
    int tamanho = strlen(texto) + 1;

    char* copia = malloc(tamanho);

    strcpy(copia, texto);

    for(int i = 0; i < tamanho; i++){
        if(isalpha((unsigned char)copia[i])){
            copia[i] = chave[copia[i] - 'a'];
        }
    }
    return copia;
}

char* decripta(char* texto, char* chave){
    int tamanho = strlen(texto) + 1;

    char* copia = malloc(tamanho);

    strcpy(copia, texto);

    int control[26] = {};

    for(int i = 0; i < 26; i++){
        control[chave[i] - 'a'] = i;
    }

    for(int i = 0; i < tamanho; i++){
        if(isalpha((unsigned char)copia[i])){
            copia[i] = control[copia[i] - 'a'] + 'a';
        }
    }

    return copia;
}

int main(){
    char op;
    scanf("%c", &op);
    getchar();
    char* linha;
    size_t tamanho = 0;
    getline(&linha, &tamanho, stdin);

    char chave[27];

    scanf("%26s", chave);
    
    char* ans = (op == 'E' ? encripta(linha, chave) : decripta(linha, chave));
    printf("%s", ans);

    free(linha);
    free(ans);

}
