#include <stdio.h>
#include "pessoa.h"

tPessoa CriaPessoa(){
    tPessoa pessoa;
    pessoa.nome[0] = '\0';
    pessoa.pai = NULL;
    pessoa.mae = NULL;
    pessoa.irmao = NULL;
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
         printf("IRMAO: ");
        if (pessoa->irmao != NULL) {
          printf("%s\n", pessoa->irmao->nome);
        } else {
            printf("NAO INFORMADO\n");
        }
        printf("\n");
    }
    
}

void AssociaFamiliasGruposPessoas(tPessoa *pessoas, int numPessoas){
    int pai, mae, filho, numA;
    scanf("\n%d", &numA);
    for(int i = 0; i<numA; i++){
        scanf("\nmae: %d, pai: %d, filho: %d", &mae, &pai, &filho);
        if (pai != -1) pessoas[filho].pai = &pessoas[pai];
        if (mae != -1) pessoas[filho].mae = &pessoas[mae];
    }
    for (int i = 0; i < numPessoas; i++) {
    for (int j = i + 1; j < numPessoas; j++) {
      if (VerificaIrmaoPessoa(pessoas + i, pessoas + j)) {
        pessoas[i].irmao = pessoas + j;
        pessoas[j].irmao = pessoas + i;
      }
    }
  }
}

int VerificaIrmaoPessoa(tPessoa *pessoa1, tPessoa *pessoa2){
    if((pessoa1->mae == pessoa2->mae) && (pessoa1->pai == pessoa2->pai)){
        return 1;
    } else return 0;
}
