#include <stdio.h>
#include "pessoa.h"

tPessoa CriaPessoa(){
    tPessoa pessoa;
    pessoa.nome[0] = '\0';
    pessoa.pai = NULL;
    pessoa.mae = NULL;

    return pessoa;
}
void LePessoa(tPessoa *pessoa){
    scanf("\n%[^\n]", pessoa->nome);
}

int VerificaSeTemPaisPessoa(tPessoa *pessoa){
    if(pessoa->pai != NULL || pessoa->mae != NULL){
        return 1;
    }
    return 0;
}

void ImprimePessoa(tPessoa *pessoa){
    
    if(VerificaSeTemPaisPessoa(pessoa)){
        printf("NOME COMPLETO: %s\n", pessoa->nome);
        if(pessoa->pai == NULL){
            printf("PAI: NAO INFORMADO\n");
        } else printf("PAI: %s\n", pessoa->pai->nome);
        if(pessoa->mae == NULL){
            printf("MAE: NAO INFORMADO\n");
        } else printf("MAE: %s\n", pessoa->mae->nome);
        printf("\n");
    }
    
}

void AssociaFamiliasGruposPessoas(tPessoa *pessoas){
    int pai, mae, filho, numA;
    scanf("\n%d", &numA);

    for(int i = 0; i<numA; i++){
        scanf("\nmae: %d, pai: %d, filho: %d", &mae, &pai, &filho);
        if (pai != -1) pessoas[filho].pai = &pessoas[pai];
        if (mae != -1) pessoas[filho].mae = &pessoas[mae];
    }
}