#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passageiro.h"

typedef struct Passageiro {
    Pessoa *pessoa;
    char *programa;
    int reservasConfirmadas;
} Passageiro;

/**
 * Cria um Passageiro. A função faz cópia interna da `Pessoa` fornecida.
 * @param pessoa Ponteiro para `Pessoa` (copiado internamente)
 * @param programa Nome do programa de fidelidade
 */
Passageiro *criaPassageiro(Pessoa *pessoa, char *programa){     
    if (!pessoa || !programa) {
        return NULL;
    }

    Passageiro *p = (Passageiro *)malloc(sizeof(Passageiro));
    if (!p) return NULL;

    p->pessoa = pessoa; 
    strcpy(p->programa = (char *)malloc(strlen(programa) + 1), programa);
    p->reservasConfirmadas = 0;

    return p;
}

/**
 * Lê um Passageiro da entrada: ler Pessoa (com `lePessoa()`), depois uma linha com o nome do programa
 * e um inteiro com os pontos.
 */
Passageiro *lePassageiro(){
    Pessoa *pessoa = lePessoa();
    if (!pessoa) return NULL;

    char programa[100];

    if (scanf(" %[^\n]", programa) != 1) {
        desalocaPessoa(pessoa);
        return NULL;
    }

    Passageiro *passageiro = criaPassageiro(pessoa, programa);
    if (!passageiro) {
        desalocaPessoa(pessoa);
        return NULL;
    }

    return passageiro;
}

/* Funções compatíveis com callbacks genéricos */
void imprimePassageiro(void *dado){
    if (!dado) return;
    Passageiro *p = (Passageiro *)dado;
    imprimePessoa((void *)p->pessoa);
    printf("- Classe: %s\n", p->programa);
    printf("- Reservas Confirmadas: %d\n", p->reservasConfirmadas);
    printf("======================\n");
}
void desalocaPassageiro(void *dado){
    if (!dado) return;
    Passageiro *p = (Passageiro *)dado;
    desalocaPessoa((void *)p->pessoa);
    free(p->programa);
    free(p);
}
int comparaPassageiro(const void *a, const void *b){
    if (!a || !b) return 0;
    Passageiro *p1 = *(Passageiro **)a;
    Passageiro *p2 = *(Passageiro **)b;
    return getReservasConfirmadas(p2) - getReservasConfirmadas(p1);
} 
int verificaCPFPassageiro(void *dado1, void *dado2){
    if (!dado1 || !dado2) return 0;
    Passageiro *p = (Passageiro *)dado1;
    if (strcmp(getCpfPassageiro(p), (char *)dado2) == 0) {
        return 1;
    }
    
    return 0;
}
/* Getters */
Pessoa *getPessoaPassageiro(Passageiro *p){
    if (!p) return NULL;
    return p->pessoa;
}
char *getProgramaPassageiro(Passageiro *p){
    if (!p) return NULL;
    return p->programa;
}
char *getCpfPassageiro(Passageiro *p){
    if (!p) return NULL;
    return getCPFPessoa(p->pessoa);
}
size_t getTamanhoPassageiro(){
    return sizeof(Passageiro);
}

/* Contador de reservas confirmadas */
void incrementaReservasConfirmadas(Passageiro *p) {
    if (!p) return;
    p->reservasConfirmadas++;
}

int getReservasConfirmadas(Passageiro *p) {
    if (!p) return 0;
    return p->reservasConfirmadas;
}
void passageiroImprimeRankingPorReservas(Passageiro **passageiros, int count, int topN){
    if (!passageiros || count <= 0) return;

    // Cria um array temporário para ordenar
    Passageiro **tempArray = (Passageiro **)malloc(count * sizeof(Passageiro *));
    if (!tempArray) return;

    for (int i = 0; i < count; i++) {
        tempArray[i] = passageiros[i];
    }

    // Ordena o array temporário por reservas confirmadas (decrescente)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (getReservasConfirmadas(tempArray[i]) < getReservasConfirmadas(tempArray[j])) {
                Passageiro *temp = tempArray[i];
                tempArray[i] = tempArray[j];
                tempArray[j] = temp;
            }
        }
    }

    // Imprime o ranking
    int limit = (topN <= 0 || topN > count) ? count : topN;
    printf("Ranking de Passageiros por Reservas Confirmadas:\n");
    for (int i = 0; i < limit; i++) {
        printf("%d. ", i + 1);
        imprimePassageiro((void *)tempArray[i]);
        printf("Reservas Confirmadas: %d\n", getReservasConfirmadas(tempArray[i]));
        printf("-------------------------\n");
    }

    free(tempArray);
}