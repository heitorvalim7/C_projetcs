#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prime.h"

struct Prime {
    int nBagagensDespachadas;
    char *tipoRefeicao; /* "COMPLETA"/"PARCIAL"/"NENHUMA" */
    char *precisaMotorista; /* "Sim"/"Nao" */
};

Prime *criaPrime(int nBagagensDespachadas, char *tipoRefeicao, char *precisaMotorista) {
    Prime *p = (Prime *)malloc(sizeof(Prime));
    if (!p) return NULL;
    p->nBagagensDespachadas = nBagagensDespachadas;
    if (tipoRefeicao) {
        p->tipoRefeicao = (char *)malloc(strlen(tipoRefeicao) + 1);
        if (p->tipoRefeicao) strcpy(p->tipoRefeicao, tipoRefeicao);
    } else p->tipoRefeicao = NULL;

    if (precisaMotorista) {
        p->precisaMotorista = (char *)malloc(strlen(precisaMotorista) + 1);
        if (p->precisaMotorista) strcpy(p->precisaMotorista, precisaMotorista);
    } else p->precisaMotorista = NULL;
    return p;
}

Prime *lePrime() {
    int nBagagens;
    char tipo[32];
    char motorista[8];

    if (scanf("%d\n", &nBagagens) != 1) return NULL;
    if (scanf(" %31s\n", tipo) != 1) return NULL;
    if (scanf(" %7s\n", motorista) != 1) return NULL;
    return criaPrime(nBagagens, tipo, motorista);
}

void imprimePrime(void *dado) {
    if (!dado) return;
    Prime *p = (Prime *)dado;
    printf("- Tipo: PRIME\n");
    printf("- Numero de Bagagens: %d\n", p->nBagagensDespachadas);
    printf("- Refeicao: %s\n", p->tipoRefeicao);
    printf("- Motorista: %s\n", p->precisaMotorista);
}

void desalocaPrime(void *dado) {
    if (!dado) return;
    Prime *p = (Prime *)dado;
    if (p->tipoRefeicao) free(p->tipoRefeicao);
    if (p->precisaMotorista) free(p->precisaMotorista);
    free(p);
}

int getNumBagagensPrime(void *dado) {
    if (!dado) return 0;
    Prime *p = (Prime *)dado;
    return p->nBagagensDespachadas;
}

char *getTipoRefeicaoPrime(void *dado) {
    if (!dado) return NULL;
    Prime *p = (Prime *)dado;
    return p->tipoRefeicao;
}

char *getPrecisaMotoristaPrime(void *dado) {
    if (!dado) return NULL;
    Prime *p = (Prime *)dado;
    return p->precisaMotorista;
}

char getTipoPrime() {
    return 'P';
}
