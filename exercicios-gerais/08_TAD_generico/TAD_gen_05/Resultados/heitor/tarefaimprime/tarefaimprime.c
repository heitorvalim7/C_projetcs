#include "tarefaimprime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct impr{
    char *msg;
};

/**
 * @brief Cria uma tarefa do tipo impressão em tela
 * @param msg - A mensagem que deve ser impressa em tela
 * @return Um ponteiro para a tarefa criada
 */
tImpr* CriaTarefaImprimir(char *msg){
    tImpr *i = (tImpr*)calloc(1, sizeof(tImpr));
    i->msg = (char*)calloc(strlen(msg)+1, sizeof(char));
    strcpy(i->msg, msg);
    return i;
}

/**
 * @brief Função que executa uma tarefa de impressão em tela
 * @param imp - Ponteiro para a tarefa a ser executada
 */
void ExecutaTarefaImprimir(void *imp){
    printf("\n%s", ((tImpr*)imp)->msg);
}

/**
 * @brief Função que destrói (libera a memória) uma tarefa de impressão em tela
 * @param imp - Ponteiro para a tarefa a ser destruída
 */
void DestroiTarefaImprimir(void *imp){
    free(((tImpr*)imp)->msg);
    free(imp);
}
