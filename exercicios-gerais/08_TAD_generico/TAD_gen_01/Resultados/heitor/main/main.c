#include "tadgen.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, tipo;
    tGeneric* gen;
    printf("tad_gen_01\n");
    printf("Digite o tipo e numero de elementos: ");
    scanf("%d %d", &tipo, &n);
    gen = CriaGenerico((Type)tipo, n);
    LeGenerico(gen);
    ImprimeGenerico(gen);
    DestroiGenerico(gen);
    return 0;
}