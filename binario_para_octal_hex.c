/*
    Conversão de Binário para Octal e Hexadecimal

    Implemente um programa em C que leia uma string de tamanho n representando um número binário positivo,
    realize a conversão direta para octal e para hexadecimal, e exiba os resultados.

    Requisitos:
    - Entrada: o tamanho n da string e a string contendo apenas os caracteres '0' e '1'
      (sem prefixos e sem espaços).
    - Armazenamento: manter os dígitos binários em um vetor (char *binario ou char binario[]).
    - Conversões necessárias:
        * Binário → Octal
        * Binário → Hexadecimal
    - Saída: imprimir o valor em octal e em hexadecimal (A–F em maiúsculas).
    - Eficiência: realizar conversões diretas por agrupamento de bits; 
      não converter para decimal como etapa intermediária.
    - Memória: liberar a string binária após a conversão e impressão dos resultados.

    Assinatura das funções:
    - char *bin_to_oct(char binario[]): retorna uma nova string com o valor convertido para octal.
    - char *bin_to_hex(char binario[]): retorna uma nova string com o valor convertido para hexadecimal.
      OBS: Usar letras maiúsculas (A–F).

    Conversão:
    - Octal: cada dígito octal corresponde a 3 bits binários.
    - Hexadecimal: cada dígito hexadecimal corresponde a 4 bits binários.

    Dicas:
    - Lembre-se do terminador nulo '\0' nas strings.
    - Garanta a liberação de toda memória alocada dinamicamente.
    - Para ler a string na próxima linha após ler n, utilize "\n" no scanf:
        scanf("%d\n", &n);
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;

char processa(char* lista, int tamanho){
    int soma = 0;
    for(int j = 0; j < tamanho; j++){
        soma += (1 << j) * (lista[j] - '0');
    }
    if(soma >= 10){
        return (soma - 10) + 'A';
    }
    return soma + '0';
}

void swap(char* lista, int a, int b){
    lista[a] ^= lista[b];
    lista[b] ^= lista[a];
    lista[a] ^= lista[b];
}

char* cresce(char* lista, char novo, int tamanho){
    char* tmp = realloc(lista, sizeof(char) * (tamanho + 2));
    tmp[tamanho] = novo;
    tmp[tamanho + 1] = '\0';
    return tmp;
}

void reverse(char* lista, int tamanho){
    int l = 0, r = tamanho - 1;

    while(l < r){
        swap(lista, l, r);
        l++;
        r--;
    }
}

void limpa(char* lista, int tamanho){
    for(int i = 0; i < tamanho; i++){
        lista[i] = '0';
    }
}

char* trata_zeros(char* lista){
    int offset = 0;
    while(lista[offset] == '0' && lista[offset + 1] != '\0'){
        offset++;
    }
    if(offset > 0){
        memmove(lista, lista + offset, strlen(lista - offset + 1));
    }
    return lista;
}

char* bin_to_oct(char binario[]){
    char temp[3] = "000";
    char* ans = malloc(1);
    
    ans[0] = '\0';

    int tamanho = 0;

    for(int i = 0; i < n; i++){
        temp[i % 3] = binario[i];
        if((i % 3) == 2 || i == n - 1){

            ans = cresce(ans, processa(temp, 3), tamanho);
            tamanho++;
            limpa(temp, 3);

        }
    }
    reverse(ans, tamanho);
    return trata_zeros(ans);
}

char* bin_to_hex(char binario[]){
    char temp[4] = "0000";
    char* ans = malloc(1);
    
    ans[0] = '\0';

    int tamanho = 0;

    for(int i = 0; i < n; i++){
        temp[i % 4] = binario[i];
        if((i % 4) == 3 || i == n - 1){

            ans = cresce(ans, processa(temp, 4), tamanho);
            tamanho++;
            limpa(temp, 4);

        }
    }
    reverse(ans, tamanho);
    return trata_zeros(ans);
}

int main(){
    scanf("%d", &n);

    char s[n + 1];

    scanf("%s", s);

    reverse(s, n);

    printf("oct: %s\n", bin_to_oct(s));
    printf("hex: %s\n", bin_to_hex(s));

}
