#include "pacote.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct pacote{
    Type type;
    int numElem;
    void* elementos;
    int somaVerificacao;
};

/**
 * @brief Cria uma estrutura genérica e dinâmica que pode armazenar um pacote a ser transmitido
 *
 * @param type - Tipo do vetor genérico. Segue o Enum definido acima.
 * @param numElem A quantidade de elementos que serão armazenados no vetor
 *
 * @return O vetor genérico
 */
tPacote* CriaPacote(Type type, int numElem){
    tPacote *pac = (tPacote*)calloc(1, sizeof(struct pacote));
    pac->type = type;
    pac->numElem = numElem;
    if(type == INT){
        pac->elementos = calloc(numElem, sizeof(int));
    } else {
        pac->elementos = calloc(numElem, sizeof(char));
    }
    return pac;
}

/**
 * @brief Destroi o vetor genérico (libera a memória alocada dinamicamente)
 *
 * @param pac - O vetor genérico que terá seu conteúdo liberado/destruído
 */
void DestroiPacote(tPacote* pac){
    free(pac->elementos);
    free(pac);
}

/**
 * @brief Lê o conteúdo do vetor genérico e salva no local adequado
 *
 * @param pac - O vetor genérico que terá seu conteúdo preenchido/lido
 */
void LePacote(tPacote* pac){
    if(pac->type == INT){
        int* elementos = (int*)pac->elementos;
        for(int i = 0; i < pac->numElem; i++){
            scanf("%d ", &elementos[i]);
        }
    } else {
        char* elementos = (char*)pac->elementos;
        for(int i = 0; i < pac->numElem; i++){
            scanf("%c", &elementos[i]);
        }
    }
}

/**
 * @brief Busca uma conta na agencia que possui um id específico
 *
 * @param pac - O vetor genérico que terá seu conteúdo impresso em tela
 */
void ImprimePacote(tPacote* pac){
    printf("%d ", pac->somaVerificacao);
    if(pac->type == INT){
        int* elementos = (int*)pac->elementos;
        for(int i = 0; i < pac->numElem; i++){
            printf("%d ", elementos[i]);
        }
    } else {
        char* elementos = (char*)pac->elementos;
        for(int i = 0; i < pac->numElem; i++){
            printf("%c", elementos[i]);
        }
        printf("\n");
    }
}

/**
 * @brief Calcula a soma de verificacao de um pacote e a armazena internamente
 *
 * @param pac - O vetor genérico que terá sua soma de verificacao calculada
 */
void CalculaSomaVerificacaoPacote(tPacote* pac){
    int soma = 0;
    if(pac->type == INT){
        int* elementos = (int*)pac->elementos;
        for(int i = 0; i < pac->numElem; i++){
            soma += elementos[i];
        }
    } else {
        char* elementos = (char*)pac->elementos;
        for(int i = 0; i < pac->numElem; i++){
            soma += (int)elementos[i];
        }
    }
    pac->somaVerificacao = soma;
}