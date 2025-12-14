#include "utils_char2.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (){
    char *vetor = CriaVetorTamPadrao();
    int t = 10;

    vetor = LeVetor(vetor, &t);
    ImprimeString(vetor);
    LiberaVetor(vetor);
}