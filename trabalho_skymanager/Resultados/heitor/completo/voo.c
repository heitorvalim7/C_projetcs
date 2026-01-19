#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voo.h"

typedef struct Voo {
    char *codigo;
    char *origem;
    char *destino;
    char *codigoAeronave;
    Data *data;
    int horaSaida;
    int horaChegada;
    float preco;
} Voo;

/**
 * Cria um Voo com os dados fornecidos.
 * @param codigo Código do voo (string)
 * @param origem Cidade/airport de origem (string)
 * @param destino Cidade/airport de destino (string)
 * @param codigoAeronave Código da aeronave (string)
 * @param data Ponteiro para `Data` (cópia não é feita automaticamente; passe uma cópia se necessário)
 * @param horaSaida Horário de saída no formato "HH:MM" (string)
 * @param horaChegada Horário de chegada no formato "HH:MM" (string)
 * @param preco Preço do voo (float)
 * @return Ponteiro para o Voo criado (ou NULL em erro)
 */
Voo *criaVoo(char *codigo, char *origem, char *destino, char *codigoAeronave, Data *data, int horaSaida, int horaChegada, float preco){
    if (!codigo || !origem || !destino || !codigoAeronave || !data || horaSaida < 0 || horaChegada < 0 || preco < 0) {
        return NULL;
    }

    Voo *v = (Voo *)malloc(sizeof(Voo));
    if (!v) return NULL;

    strcpy(v->codigo = (char *)malloc(strlen(codigo) + 1), codigo);
    strcpy(v->origem = (char *)malloc(strlen(origem) + 1), origem);
    strcpy(v->destino = (char *)malloc(strlen(destino) + 1), destino);
    strcpy(v->codigoAeronave = (char *)malloc(strlen(codigoAeronave) + 1), codigoAeronave);
    v->data = data; // Assume ownership of the Data pointer
    v->horaSaida = horaSaida;
    v->horaChegada = horaChegada;
    v->preco = preco;

    return v;
}
/** Lê um Voo da entrada padrão conforme especificação do trabalho */
Voo *leVoo(){
    char codigo[21], origem[31], destino[31], codigoAeronave[100];
    int horaSaida, horaChegada;
    float preco;

    if (scanf(" %20[^\n]", codigo) != 1) return NULL;
    if (scanf(" %30[^\n]", origem) != 1) return NULL;
    if (scanf(" %30[^\n]", destino) != 1) return NULL;
    if (scanf(" %99[^\n]", codigoAeronave) != 1) return NULL;
    Data *data = leData();
    if (!data) return NULL;
    if (scanf("%d\n", &horaSaida) != 1) {
        desalocaData(data);
        return NULL;
    }
    if (scanf("%d\n", &horaChegada) != 1) {
        desalocaData(data);
        return NULL;
    }
    if (scanf("%f\n", &preco) != 1) {
        desalocaData(data);
        return NULL;
    }

    Voo *v = criaVoo(codigo, origem, destino, codigoAeronave, data, horaSaida, horaChegada, preco);
    if (!v) {
        desalocaData(data);
        return NULL;
    }
    return v;
}

/** Desaloca um Voo (compatível com callbacks genéricos) */
void desalocaVoo(void *dado){
    if (!dado) return;
    Voo *v = (Voo *)dado;
    free(v->codigo);
    free(v->origem);
    free(v->destino);
    free(v->codigoAeronave);
    desalocaData(v->data);
    free(v);
}

/** Comparação por código do voo (retorna 1 se iguais, 0 caso contrário) */
int comparaVoo(const void *a, const void *b){
    if (!a || !b) return 0;
    Voo *v1 = (Voo *)a;
    Voo *v2 = (Voo *)b;
    return strcmp(v1->codigo, v2->codigo) == 0;
}

int verificaCodigoVoo(void *dado, void *chave){
    if (!dado || !chave) return 0;
    Voo *v = (Voo *)dado;
    return strcmp(getCodigoVoo(v), (char *)chave) == 0;
}

void imprimeVoo(void *dado){
    Voo *v = (Voo *)dado;
    if(!v) return;
    printf("Codigo: %s\n", v->codigo);
    printf("Origem: %s\n", v->origem);
    printf("Destino: %s\n", v->destino);
    printf("Codigo Aeronave: %s\n", v->codigoAeronave);
    printf("Data: ");
    imprimeData(v->data);
    printf("Hora Saida: %02d\n", v->horaSaida);
    printf("Hora Chegada: %02d\n", v->horaChegada);
    printf("Preco: %.2f\n", v->preco);
}


/** Getters */
char *getCodigoVoo(Voo *v){
    return v ? v->codigo : NULL;    
}
char *getOrigemVoo(Voo *v){
    return v ? v->origem : NULL;    
}
char *getDestinoVoo(Voo *v){    
    return v ? v->destino : NULL;    
}   
char *getCodigoAeronaveVoo(Voo *v){
    return v ? v->codigoAeronave : NULL;
}
Data *getDataVoo(Voo *v){
    return v ? v->data : NULL;
}
int getHoraSaidaVoo(Voo *v){
    return v ? v->horaSaida : -1;
}
int getHoraChegadaVoo(Voo *v){
    return v ? v->horaChegada : -1;
}
float getPrecoVoo(Voo *v){
    return v ? v->preco : -1;
}
