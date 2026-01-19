#include "tadgen.h"
#include <stdio.h>
#include <stdlib.h>

struct generic{
    Type type;
    int numElem;
    void* elementos;
};

/**
 * @brief Cria uma estrutura genérica e dinâmica que pode armazenar tanto inteiros quanto floats
 *
 * @param type - Tipo do vetor genérico. Segue o Enum definido acima.
 * @param numElem A quantidade de elementos que serão armazenados no vetor
 *
 * @return O vetor genérico
 */
tGeneric* CriaGenerico(Type type, int numElem){
    tGeneric* gen = (tGeneric*)calloc(1, sizeof(tGeneric));
    gen->type = type;
    gen->numElem = numElem;
    if(type == INT){
        gen->elementos = calloc(numElem, sizeof(int));
    } else {
        gen->elementos = calloc(numElem, sizeof(float));
    }
    return gen;
}

/**
 * @brief Destroi o vetor genérico (libera a memória alocada dinamicamente)
 *
 * @param gen - O vetor genérico que terá seu conteúdo liberado/destruído
 */
void DestroiGenerico(tGeneric* gen){
    free(gen->elementos);
    free(gen);  
}

/**
 * @brief Lê o conteúdo do vetor genérico e salva no local adequado
 *
 * @param gen - O vetor genérico que terá seu conteúdo preenchido/lido
 */
void LeGenerico(tGeneric* gen){
    printf("\nDigite o vetor:\n");
    if(gen->type == INT){
        int* elementos = (int*)gen->elementos;
        for(int i = 0; i < gen->numElem; i++){
            scanf(" %d", &elementos[i]);
        }
    } else {
        float* elementos = (float*)gen->elementos;
        for(int i = 0; i < gen->numElem; i++){
            scanf(" %f", &elementos[i]);
        }
    }
}

/**
 * @brief Busca uma conta na agencia que possui um id específico
 *
 * @param gen - O vetor genérico que terá seu conteúdo impresso em tela
 */
void ImprimeGenerico(tGeneric* gen){
    if(gen->type == INT){
        int* elementos = (int*)gen->elementos;
        for(int i = 0; i < gen->numElem; i++){
            printf("%d ", elementos[i]);
        }
    } else {
        float* elementos = (float*)gen->elementos;
        for(int i = 0; i < gen->numElem; i++){
            printf("%.2f ", elementos[i]);
        }
    }
}