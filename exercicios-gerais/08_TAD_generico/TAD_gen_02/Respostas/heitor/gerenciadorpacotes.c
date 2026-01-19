#include "gerenciadorpacotes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INCREMENTO 5

struct gerenciadorpacotes{
    tPacote** pacotes;
    int tamanho;
};

/**
 * @brief Cria uma TAD que gerencia pacotes. O pacote é um TAD genérico.
 *
 *
 * @return O gerenciador de pacotes
 */
tGerenciador* CriaGerenciador(){
    tGerenciador* geren = (tGerenciador*)calloc(1, sizeof(struct gerenciadorpacotes));
    geren->pacotes = (tPacote**)calloc(INCREMENTO, sizeof(tPacote*));
    geren->tamanho = 0;
    return geren;
}

/**
 * @brief Adiciona um pacote ao gerenciador de pacotes.
 *
 * @param geren O gerenciador de pacotes que armazenará o pacote 
 * @param pac O pacote que queremos adicionar no gerenciador.
 *
 */
void AdicionaPacoteNoGerenciador(tGerenciador* geren, tPacote* pac){
    if(geren->tamanho % INCREMENTO == 0 && geren->tamanho != 0){
        geren->pacotes = (tPacote**)realloc(geren->pacotes, (geren->tamanho + INCREMENTO) * sizeof(tPacote*));
    }
    geren->pacotes[geren->tamanho] = pac;
    geren->tamanho++;
}


/**
 * @brief Destrói um gerenciador de pacotes
 *
 * @param geren O gerenciador de pacotes que será destruído (memória liberada)
 *
 */
void DestroiGerenciador(tGerenciador* geren){
    for(int i = 0; i < geren->tamanho; i++){
        DestroiPacote(geren->pacotes[i]);
    }
    free(geren->pacotes);
    free(geren);
}

/**
 * @brief Imprime um pacote específico do gerenciador de pacotes.
 *
 * @param geren - O gerenciador de pacotes que terá um pacote impresso
 * @param idx - O índice do pacote a ser impresso (começa em zero!)
 *
 */
void ImprimirPacoteNoIndice(tGerenciador* geren, int idx){
    if(idx < 0 || idx >= geren->tamanho){
        printf("Indice invalido\n");
        return;
    }
    ImprimePacote(geren->pacotes[idx]);
}


/**
 * @brief Imprime todos os pacotes de um gerenciador de pacotes
 *
 * @param geren O gerenciador de pacotes que terá seus pacotes impressos
 *
 */
void ImprimirTodosPacotes(tGerenciador* geren){
    for(int i = 0; i < geren->tamanho; i++){
        ImprimePacote(geren->pacotes[i]);
        printf("\n");
    }
}