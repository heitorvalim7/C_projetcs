#include "vetor.h"

void LeDadosParaVetor(int * vet, int tam){
    for(int i = 0; i<tam; i++){
        scanf("%d", vet+i);
    }
}

void ImprimeDadosDoVetor(int * n, int tam){
    for(int i = 0; i<tam; i++){
        printf("%d ", *(n+i));
    }
    printf("\n");
}

void TrocaSeAcharMenor(int * vet, int tam, int * paraTrocar){
    
    for(int i = 0; i<tam; i++){
        if(*(vet+i) < *paraTrocar ){
            *paraTrocar = *(vet + i);
        }
    }
}

void OrdeneCrescente(int * vet, int tam){
    for(int i = 0; i<tam-1; i++){
        for(int j = i+1; j<tam; j++){
            if(*(vet + i) > *(vet+j)){
                int troca;
                troca = *(vet+i);
                *(vet + i) = *(vet+j);
                *(vet+j) = troca;
            }
        }
    }
}