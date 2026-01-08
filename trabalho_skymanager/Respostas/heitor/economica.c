#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "economica.h"

struct Economica {
    int nBagagens;
    char assentoEspecial[TAM_ASSENTO_ESPECIAL];
};

/**
 * @brief Cria uma nova reserva do tipo Econômica
 * @param nBagagens Número de bagagens permitidas
 * @param assentoEspecial Assento especial solicitado
 * @return Ponteiro para a nova reserva criada
 */
Economica *criaEconomica(int nBagagens, char *assentoEspecial){
    if (!assentoEspecial) return NULL;  
    Economica *e = (Economica *)malloc(sizeof(Economica));
    if (!e) return NULL;
    e->nBagagens = nBagagens;
    strcpy(e->assentoEspecial, assentoEspecial);
    return e;
}

/**
 * @brief Lê os dados de uma reserva do tipo Econômica a partir da entrada padrão de acordo com a especificação do trabalho
 * @return Ponteiro para a nova reserva criada
 */
Economica *leEconomica(){
    int nBagagens;
    char assentoEspecial[TAM_ASSENTO_ESPECIAL];

    if (scanf("%d\n", &nBagagens ) != 1) {
        return NULL;
    }
    if (scanf("%3s\n", assentoEspecial) != 1) {
        return NULL;
    }

    return criaEconomica(nBagagens, assentoEspecial);
}

/**
 * @brief Imprime os detalhes de uma reserva do tipo Econômica
 * @param dado Ponteiro genérico para a reserva do tipo Econômica
 */
void imprimeEconomica(void *dado){
    if (!dado) return;
    Economica *e = (Economica *)dado;
    printf("- Tipo: ECONOMICA\n");
    printf("- Numero de Bagagens: %d\n", e->nBagagens);
    printf("- Assento Especial: %s\n", e->assentoEspecial);
}

/**
 * @brief Desaloca a memória associada a uma reserva do tipo Econômica
 * @param dado Ponteiro genérico para a reserva do tipo Econômica
 */
void desalocaEconomica(void *dado){
    if (!dado) return;
    Economica *e = (Economica *)dado;
    free(e);
}

/**
 * @brief Obtém o número de bagagens permitidas em uma reserva do tipo Econômica
 * @param dado Ponteiro genérico para a reserva do tipo Econômica
 * @return Número de bagagens permitidas
 */
int getNumBagagensEconomica(void *dado){
    if (!dado) return 0;
    Economica *e = (Economica *)dado;
    return e->nBagagens;
}

/**
 * @brief Obtém o tipo da reserva do tipo Econômica
 * @return Caractere representando o tipo da reserva ('E' para Econômica)
 */
char getTipoEconomica(){
    return 'E';
}