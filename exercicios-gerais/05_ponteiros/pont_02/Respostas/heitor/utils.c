#include <stdio.h>
#include "utils.h"

void LeIntervalo(int * m, int * n){
    scanf("%d %d\n", m, n);
}

int EhPrimo(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}   
void ObtemMaiorEMenorPrimo(int m, int n, int *menor, int *maior){
    int flag = 1;
    for(int i = m; i <= n; i++){
        if (EhPrimo(i)) {
            if (flag) {
                *menor = i;
                flag = 0;
            }
            *maior = i;
        }
    }
}