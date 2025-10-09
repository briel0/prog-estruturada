/*
Implementação da Função `palindromo`

Crie um programa que implementa uma função em C que verifica se uma determinada
string é um palíndromo, considerando algumas regras de normalização.

Definição de Palíndromo:
Uma string é considerada um palíndromo se pode ser lida da mesma forma da esquerda
para a direita e da direita para a esquerda após a aplicação das seguintes regras:

1. Ignorar espaços e pontuação:
   A comparação deve ser feita apenas entre caracteres alfanuméricos (letras e dígitos).

2. Ignorar diferença entre maiúsculas e minúsculas (case-insensitive):
   Caracteres como 'A' e 'a' devem ser tratados como equivalentes.

3. Considerar apenas ASCII básico:
   Não é necessário tratar acentuação ou diacríticos (por exemplo, "á", "ç").
   O exercício assume que você trabalhará com o conjunto de caracteres ASCII padrão.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int palindromo(const char s[]){
    int tam = strlen(s);

    int l = 0, r = tam - 2;

    while(l <= r){
        while(l < tam && !isalnum(s[l])){
            l++;
        }
        while(r > 0 && !isalnum(s[r])){
            r--;
        }
        if(s[l] != s[r]){
            return false;
        }
        l++;
        r--;
    }
    return true;
}

int main(){
    char s[100000];
    fgets(s, sizeof(s), stdin);

    printf("\"");

    int tam = strlen(s);

    for(int i = 0; i < tam; i++){
        s[i] = tolower((unsigned char)s[i]);
    }

    for(int i = 0; i < tam - 1; i++){
        printf("%c", s[i]);
    }

    printf("\" ");

    if(!palindromo(s)){
        printf("não ");
    }

    printf("é palíndromo");

}
