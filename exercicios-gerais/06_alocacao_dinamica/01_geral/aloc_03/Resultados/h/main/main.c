#include "utils_char.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    char *vetor;
    int tamanho;
    scanf("%d\n", &tamanho);
    vetor = CriaVetor(tamanho);
    ImprimeString(vetor, tamanho);
    LeVetor(vetor, tamanho);
    ImprimeString(vetor, tamanho);
    LiberaVetor(vetor);
}