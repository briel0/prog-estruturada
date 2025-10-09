/*
Neste exercício, você vai implementar uma função recursiva para resolver o problema da maior soma de um subvetor contíguo de inteiros (conhecido como maximum subarray). 
*/

#include <stdio.h>

int MaiorSomaSubvetor(const int a[], int l, int r){
    if(l == r){
        return a[l];
    }
    int mid = (l + r) / 2;
    int sufixo = a[mid];
    int soma = 0;
    for(int i = mid; i >= l; i--){
        soma += a[i];
        if(soma > sufixo){
            sufixo = soma;
        }
    }
    
    int prefixo = a[mid + 1];
    soma = 0;
    for(int i = mid + 1; i <= r; i++){
        soma += a[i];
        if(soma > prefixo){
            prefixo = soma;
        }
    }
    
    int ans = sufixo + prefixo;
    
    int esquerda = MaiorSomaSubvetor(a, l, mid);
    int direita = MaiorSomaSubvetor(a, mid + 1, r);
    
    if(esquerda > ans){
        ans = esquerda;
    }
    if(direita > ans){
        ans = direita;
    }
    return ans;
}

int main(){
    int n;
    scanf("%d", &n);
    
    int v[n];
    
    printf("Vetor: ");
    
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
        printf("%d ", v[i]);
    }
        
    printf("\n");
    
    printf("Maior soma: %d\n", MaiorSomaSubvetor(v, 0, n - 1));
    
    return 0;
}
