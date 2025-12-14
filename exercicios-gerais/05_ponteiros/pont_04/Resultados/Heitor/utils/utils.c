#include "utils.h"

void LeNumeros(int *array, int tamanho){
    for(int i = 0; i<tamanho; i++){
        scanf("%d", array+i);
    }
}
void EncontraMaiorMenorMedia(int *array, int tamanho, int *maior, int *menor, float *media){
    *maior = *array;
    *menor = *array;
    *media = 0;
    for(int i = 0; i<tamanho; i++){
        if(*maior < *(array + i)){
            *maior = *(array+i);
        }
        if(*menor > *(array+i)){
            *menor = *(array+i);
        }
        *media += *(array + i);
        
    }
    *media /= tamanho;
}