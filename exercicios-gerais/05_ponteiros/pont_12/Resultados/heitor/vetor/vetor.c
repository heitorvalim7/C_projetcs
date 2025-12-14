#include "vetor.h"
#include <stdio.h>

void LeVetor(Vetor *vetor){
    scanf("%d\n", &vetor->tamanhoUtilizado);
    for(int i = 0; i<vetor->tamanhoUtilizado; i++){
        scanf("%d ", &vetor->elementos[i]);
    }
}
int AplicarOperacaoVetor(Vetor *vetor, Operation op){
    if (vetor->tamanhoUtilizado == 0) return 0; 
    if (vetor->tamanhoUtilizado == 1) return vetor->elementos[0];

    int resultado = op(vetor->elementos[0], vetor->elementos[1]);
    for(int i=2; i<vetor->tamanhoUtilizado; i++){
        resultado = op(resultado, vetor->elementos[i]);
    }
    return resultado;
}
