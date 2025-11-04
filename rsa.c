/*
Implementação Simplificada do RSA em C

Objetivo:
Implementar encriptação e decriptação RSA caractere por caractere,
usando exponenciação modular com números até 64 bits (unsigned long long).

Conceito:
- RSA usa duas chaves: pública (e, n) e privada (d, n).
- Encriptação:  C = M^e mod n
- Decriptação:  M = C^d mod n
  Onde M é o número correspondente ao caractere ('a'→0, ..., 'z'→25).

Funções Principais:
1. multiply_mod(a, b, m): calcula (a * b) % m evitando overflow.
2. modular_exponentiation(base, exp, mod): calcula (base^exp) % mod com “exponenciação rápida”.
3. encrypt_string(plaintext, e, n): encripta string → vetor de números cifrados.
4. decrypt_string(cipher_array, len, d, n): decripta vetor → string original.
5. print_result(data, len, type):
   - 'E': imprime valores cifrados em hexadecimal.
   - 'D': imprime texto decriptado como string.

main():
- Lê operação ('E' para encriptar, 'D' para decriptar).
- Lê chaves (em hexadecimal) e entrada (texto ou hex).
- Executa encriptação/decriptação.
- Exibe resultado e libera memória.

Notas:
- Todas as variáveis numéricas são unsigned long long.
- Entradas e saídas de chaves em formato hexadecimal (%llx / %llX).
- Exemplo:
  Chave pública: e = 10001, n = 2273D04C69E5
  Chave privada: d = 20B50064A08D, n = 2273D04C69E5
*/

#include <stdio.h>
#include <stdlib.h>

unsigned long long modmul(unsigned long long a, unsigned long long b, unsigned long long mod){
    unsigned __int128 t = (unsigned __int128)a * b;
    return (unsigned long long)(t % mod);
}

unsigned long long binexp(unsigned long long base, unsigned long long expo, unsigned long long mod){
    unsigned long long ans = 1ULL;
    base = base % mod;
    while(expo){
        if(expo & 1ULL){
            ans = modmul(base, ans, mod);
        }
        base = modmul(base, base, mod);
        expo >>= 1ULL;
    }
    return ans;
}

void encriptar(char* palavra, unsigned long long e, unsigned long long n, int tamanho){
    for(int i = 0; i < tamanho; i++){
        unsigned long long c = palavra[i] - 'a';
        unsigned long long atual = binexp(c, e, n);
        printf("%llX ", atual);
    }
}

void decriptar(unsigned long long d, unsigned long long n){
    unsigned long long temp;

    while(scanf("%llx", &temp) == 1){
        unsigned long long ans = binexp(temp, d, n);
        char a = ans + 'a';
        printf("%c", a);
    }
    
}

int main(){
    char op;
    scanf(" %c", &op);

    if(op == 'E'){
        unsigned long long e, n;
        scanf("%llx %llx", &e, &n);

        char* palavra = malloc(1);
        int tamanho = 0;
        palavra[0] = '\0';

        char temp;

        while(scanf(" %c", &temp) == 1 && temp != '\n'){
            palavra = realloc(palavra, tamanho + 2);
            palavra[tamanho] = temp;
            palavra[++tamanho] = '\0';
        }
        
        encriptar(palavra, e, n, tamanho);
        return 0;
    }

    unsigned long long e, n;
    scanf("%llx %llx", &e, &n);

    decriptar(e, n);

}
