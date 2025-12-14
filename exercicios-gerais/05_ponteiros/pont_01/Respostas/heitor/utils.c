#include "utils.h"

int TrocaInterios(int * n1, int * n2){
    if(*n1 > *n2){
        int troca; 
        troca = *n1;
        *n1 = *n2;
        *n2 = troca;
        return 1;
    }
    return 0;
}
