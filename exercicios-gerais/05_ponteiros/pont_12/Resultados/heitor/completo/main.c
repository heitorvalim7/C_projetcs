#include <stdio.h>
#include "vetor.h"

int soma(int n1, int n2){
    return n1 +n2;
}
int multiplica(int n1, int n2){
    return n1 * n2;
}

int main(){
    Vetor v;
    Operation op;
    LeVetor(&v);
    op = soma;
    int resultados = AplicarOperacaoVetor(&v, op);
    op = multiplica;
    int resultadom = AplicarOperacaoVetor(&v, op);
    printf("Soma: %d\n", resultados);
    printf("Produto: %d\n", resultadom);

}