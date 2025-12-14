#include <stdio.h>
#include <stdlib.h>
#include "pessoa.h"

int main(){
    int n;
    scanf("%d", &n);

    tPessoa pessoas[n];
    for(int i = 0; i<n; i++){
        pessoas[i]=CriaPessoa();
        LePessoa(&pessoas[i]);
    }
    
    AssociaFamiliasGruposPessoas(pessoas, n);
    for(int i = 0; i<n; i++){
        ImprimePessoa(&pessoas[i]);
    }
    return 0;
}