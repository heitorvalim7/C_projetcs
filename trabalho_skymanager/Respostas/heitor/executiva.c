#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "executiva.h"

struct Executiva {
    int nBagagens;
    char acessoLounge[TAM_ASSENTO_ESPECIAL];
    char precisaRefeicao[TAM_ASSENTO_ESPECIAL];
};

Executiva *criaExecutiva(int nBagagens, char *acessoLounge, char *precisaRefeicao){
    Executiva *e = (Executiva *)malloc(sizeof(Executiva));
    if (!e) return NULL;
    e->nBagagens = nBagagens;
    strcpy(e->acessoLounge, acessoLounge);
    strcpy(e->precisaRefeicao, precisaRefeicao);

    return e;
}

Executiva *leExecutiva(){
    int nBagagens;
    char acesso[TAM_ASSENTO_ESPECIAL];
    char refeicao[TAM_ASSENTO_ESPECIAL];
    if (scanf("%d", &nBagagens) != 1) return NULL;
    if (scanf("%s", refeicao) != 1) return NULL;
    if (scanf("%s", acesso) != 1) return NULL;
    return criaExecutiva(nBagagens, acesso, refeicao);
}

void imprimeExecutiva(void *dado){
    if (!dado) return;
    Executiva *e = (Executiva *)dado;
    printf("- Tipo: EXECUTIVA\n");
    printf("- Numero de Bagagens: %d\n", e->nBagagens);
    printf("- Refeicao Especial: %s\n", e->precisaRefeicao);
    printf("- Acesso ao Lounge: %s\n", e->acessoLounge);

}

void desalocaExecutiva(void *dado){
    if (!dado) return;
    Executiva *e = (Executiva *)dado;
    free(e);
}

int getNumBagagensExecutiva(void *dado){
    if (!dado) return 0;
    Executiva *e = (Executiva *)dado;
    return e->nBagagens;
}

char *getAcessoLoungeExecutiva(void *dado){
    if (!dado) return NULL;
    Executiva *e = (Executiva *)dado;
    return e->acessoLounge;
}

char *getPrecisaRefeicaoExecutiva(void *dado){
    if (!dado) return NULL;
    Executiva *e = (Executiva *)dado;
    return e->precisaRefeicao;
}

char getTipoExecutiva(){
    return 'X';
}
