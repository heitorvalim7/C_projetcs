#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeronave.h"

typedef struct Aeronave {
    char *codigo;
    char *modelo;
    int capacidade;
} Aeronave;

/**
 * Cria uma Aeronave.
 * @param codigo Código da aeronave (string)
 * @param modelo Modelo da aeronave (string)
 * @param capacidade Capacidade (número de passageiros)
 * @return Ponteiro para a Aeronave criada
 */
Aeronave *criaAeronave(char *codigo, char *modelo, int capacidade){
    if (!codigo || !modelo || capacidade <= 0) {
        return NULL;
    }

    Aeronave *a = (Aeronave *)malloc(sizeof(Aeronave));
    if (!a) return NULL;

    strcpy(a->codigo = (char *)malloc(strlen(codigo) + 1), codigo);
    strcpy(a->modelo = (char *)malloc(strlen(modelo) + 1), modelo);
    a->capacidade = capacidade;

    return a;
}

/** Lê uma Aeronave da entrada padrão (codigo, modelo, capacidade) */
Aeronave *leAeronave(){
    char codigo[21], modelo[51];
    int capacidade;

    if (scanf(" %20[^\n]", codigo) != 1) return NULL;
    if (scanf(" %50[^\n]", modelo) != 1) return NULL;
    if (scanf("%d", &capacidade) != 1) return NULL;

    return criaAeronave(codigo, modelo, capacidade);
}

void imprimeAeronave(void *dado){
    if (!dado) return;
    Aeronave *a = (Aeronave *)dado;
    printf("Código: %s\n", a->codigo);
    printf("Modelo: %s\n", a->modelo);
    printf("Capacidade: %d\n", a->capacidade);
}

/** Desaloca uma Aeronave (compatível com callbacks genéricos) */
void desalocaAeronave(void *dado){
    if (!dado) return;
    Aeronave *a = (Aeronave *)dado;
    free(a->codigo);
    free(a->modelo);
    free(a);
}

/** Compara por código (retorna 1 se iguais, 0 caso contrário) */
int comparaAeronave(const void *a, const void *b){
    if (!a || !b) return 0;
    Aeronave *aa = (Aeronave *)a;
    Aeronave *bb = (Aeronave *)b;
    return strcmp(aa->codigo, bb->codigo) == 0;
}

int verificaCodigoAeronave(void *dado, void *chave){
    if (!dado || !chave) return 0;
    Aeronave *a = (Aeronave *)dado;
    return strcmp(getCodigoAeronave(a), (char *)chave) == 0;
}

/** Getters */
char *getCodigoAeronave(Aeronave *a){
    if (!a) return NULL;
    return a->codigo;
}
char *getModeloAeronave(Aeronave *a){
    if (!a) return NULL;
    return a->modelo;
}
int getCapacidadeAeronave(Aeronave *a){
    if (!a) return -1;
    return a->capacidade;
}